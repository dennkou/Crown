#include "RenderSystem.h"
#include <dxgi1_6.h>
#include <string>
#include "./../Window.h"
#include "DirectXTex.h"
#include "d3dx12.h"
#include "DirectX12Wraps/DescriptorHeaps.h"
#include "DirectX12Wraps/ResourceUploader.h"
#include "Shader.h"
#include "Camera.h"

//	ライブラリのリンクだよ☆
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

Crown::RenderObject::RenderSystem::RenderSystem(Crown::Window& renderTargetWindow)
	:
	m_device(nullptr),
	m_renderTargetWindow(renderTargetWindow),
	m_swapChain(),
	m_commandList(),
	m_modelManager()
{
}

Crown::RenderObject::RenderSystem::~RenderSystem()
{
	m_commandList.RunAndWait();
	ResourceUploader::DeleteInstance();
	Shader::DeleteInstance();
	DescriptorHeaps::DeleteDescriptorHeaps();
	Camera::DelteInstance();
}

void Crown::RenderObject::RenderSystem::Initialize()
{
	//	デバックレイヤーを起動するよ☆
	{
		#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug> debugLayer;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
		debugLayer->EnableDebugLayer();
		#endif // _DEBUG
	}
	//	m_deviceの作成を行うよ☆
	{
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

		Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory = nullptr;
		CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgiFactory));	//	DXGIFactoryの作成だよ☆

		Microsoft::WRL::ComPtr<IDXGIAdapter> tmpAdapter;
		Microsoft::WRL::ComPtr<IDXGIAdapter> selectAdapter;
		//	GPUデバイスの全取得だよ☆
		for (int i = 0; dxgiFactory->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			DXGI_ADAPTER_DESC adesc = {};
			tmpAdapter->GetDesc(&adesc);

			std::wstring strDesc = adesc.Description;
			if (strDesc.find(L"NVIDIA") != std::string::npos || strDesc.find(L"AMD") != std::string::npos)
			{
				selectAdapter = tmpAdapter;
				break;
			}
		}
		//	Direct3Dデバイスの初期化だよ☆
		D3D12CreateDevice(selectAdapter.Get(), level, IID_PPV_ARGS(&m_device));		//	D3D12Deviceの作成だよ☆
	}
	m_commandList.Initialize(m_device.Get(), 1, 0);
	m_swapChain.Initialize(m_device.Get(), &m_renderTargetWindow, m_commandList.GetCommandQueue(), 2);
	ResourceUploader::CreateResourceUploader(m_device.Get(), m_commandList);
	DescriptorHeaps::CreateDescriptorHeaps(m_device.Get());
	m_textureBuffer.Initialize(m_device.Get(),m_commandList.GetCopyCommandList(), &DescriptorHeaps::GetInstance());
	m_modelManager.Initialize(m_device.Get(), &m_textureBuffer);
	Camera::CreateInstance(m_device.Get());
}





void Crown::RenderObject::RenderSystem::Update()
{
	//	描画開始☆
	{
		CD3DX12_RESOURCE_BARRIER tmp = CD3DX12_RESOURCE_BARRIER::Transition(m_swapChain.GetBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);	//	リソースバリアをの設定をすべてに使用可能から描画先として使用に切り替えるよ☆
		m_commandList.GetGraphicsCommandList()->ResourceBarrier(1, &tmp);																									//	リソースバリアの設定変更を要求するよ☆
	}
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH = m_swapChain.GetRenderTargetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
	rtvH.ptr += static_cast<SIZE_T>(m_swapChain.GetBackBufferIndex()) * m_swapChain.GetRenderTargetViewSize();

	const D3D12_CPU_DESCRIPTOR_HANDLE CPU_DESCRIPTOR_HANDLE = m_swapChain.GetDepthStencilDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

	m_commandList.GetGraphicsCommandList()->OMSetRenderTargets(1, &rtvH, false, &CPU_DESCRIPTOR_HANDLE);																	//	レンダーターゲットを指定するよ☆

	//	画面を初期化☆
	float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_commandList.GetGraphicsCommandList()->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	m_commandList.GetGraphicsCommandList()->ClearDepthStencilView(CPU_DESCRIPTOR_HANDLE, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	D3D12_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(m_renderTargetWindow.GetWindowWidth() * 2);
	viewport.Height = static_cast<float>(m_renderTargetWindow.GetWindowHeight() * 2);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;

	D3D12_RECT scissorrect = {};
	scissorrect.top = 0;
	scissorrect.left = 0;
	scissorrect.right = static_cast<LONG>(m_renderTargetWindow.GetWindowWidth() * 2);
	scissorrect.bottom = static_cast<LONG>(m_renderTargetWindow.GetWindowHeight() * 2);

	m_commandList.GetGraphicsCommandList()->RSSetViewports(1, &viewport);
	m_commandList.GetGraphicsCommandList()->RSSetScissorRects(1, &scissorrect);
	ID3D12DescriptorHeap* descriptorHeap = DescriptorHeaps::GetInstance().GetDescriptorHeap();
	m_commandList.GetGraphicsCommandList()->SetDescriptorHeaps(1, &descriptorHeap);



	m_modelManager.Draw(MaterialTag::Normal,m_commandList);



	//	描画終了～☆
	{
		CD3DX12_RESOURCE_BARRIER tmp = CD3DX12_RESOURCE_BARRIER::Transition(m_swapChain.GetBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);	//	リソースバリアをの設定をすべてに使用可能にするよ☆
		m_commandList.GetGraphicsCommandList()->ResourceBarrier(1, &tmp);
	}
	m_commandList.RunAndWait();
	ResourceUploader::GetInstance()->DeleteUploadResource();
	m_swapChain.Present(0);

	DescriptorHeaps::GetInstance().ResetDescriptorHeapFlag();
}