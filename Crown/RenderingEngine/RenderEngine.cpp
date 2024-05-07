#include "RenderEngine.h"

Crown::RenderEngine::RenderEngine(Window* renderTarget)
{
	m_renderTarget = renderTarget;
	//	デバックレイヤーを起動するよ☆
	{
#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug> debugLayer;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
		debugLayer->EnableDebugLayer();
#endif // _DEBUG
	}
	//	deviceの作成を行うよ☆
	{
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

		//	DXGIFactoryを作成するよ☆
		Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory = nullptr;
		CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgiFactory));

		//	GPUを列挙してdGPUを探すよ☆
		Microsoft::WRL::ComPtr<IDXGIAdapter1> tmpAdapter;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> selectAdapter;
		for (int i = 0; dxgiFactory->EnumAdapters1(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			DXGI_ADAPTER_DESC1 adapterDesc = {};
			tmpAdapter->GetDesc1(&adapterDesc);
			if ((!(adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)) && (adapterDesc.DedicatedVideoMemory > 0))
			{
				selectAdapter = tmpAdapter;
				break;
			}
		}
		//	Direct3Dデバイスの初期化だよ☆
		D3D12CreateDevice(selectAdapter.Get(), level, IID_PPV_ARGS(&m_device));		//	D3D12Deviceの作成だよ☆
	}

	m_resourceManager.reset(new ResourceManager(m_device));
	GPUThreadsSetup();
	m_swapChain.Initialize(m_device.Get(), renderTarget, m_gpuThread.GetCommandQueue().Get(), BackBufferNum);

}

Crown::RenderEngine::~RenderEngine()
{
	//	全スレッドを待機するよ☆
	m_gpuThread.CPUWait();
	for (std::shared_ptr<CommandList>& commandList : m_commandLists)
	{
		commandList->Reset();
		commandList.reset();
	}
}

void Crown::RenderEngine::Render()
{
	if (m_gpuThread.IsEnd())
	{
		m_gpuThread.CPUWait();
		m_swapChain.Present(0);
		RebuildPipeline();
		m_resourceManager->CopyExecuton();
		m_gpuThread.Executon();
	}
}

void Crown::RenderEngine::RebuildPipeline()
{
	m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->Reset();
	{
		//	描画開始☆
		{
			CD3DX12_RESOURCE_BARRIER tmp = CD3DX12_RESOURCE_BARRIER::Transition(m_swapChain.GetBackBuffer().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);	//	リソースバリアをの設定をすべてに使用可能から描画先として使用に切り替えるよ☆
			m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ResourceBarrier(1, &tmp);																									//	リソースバリアの設定変更を要求するよ☆
		}
		//	描画対象の決定☆
		D3D12_CPU_DESCRIPTOR_HANDLE rtvH = m_swapChain.GetRenderTargetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvH.ptr += static_cast<SIZE_T>(m_swapChain.GetBackBufferIndex()) * m_swapChain.GetRenderTargetViewSize();
		const D3D12_CPU_DESCRIPTOR_HANDLE CPU_DESCRIPTOR_HANDLE = m_swapChain.GetDepthStencilDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

		//	画面を初期化☆
		float clearColor[4]{ 0,1,1,1 };
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ClearDepthStencilView(CPU_DESCRIPTOR_HANDLE, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &CPU_DESCRIPTOR_HANDLE);																	//	レンダーターゲットを指定するよ☆

		D3D12_VIEWPORT viewport = {};
		viewport.Width = static_cast<float>(m_renderTarget->GetWindowWidth() * 2);
		viewport.Height = static_cast<float>(m_renderTarget->GetWindowHeight() * 2);
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->RSSetViewports(1, &viewport);
		D3D12_RECT scissorrect = {};
		scissorrect.top = 0;
		scissorrect.left = 0;
		scissorrect.right = static_cast<LONG>(m_renderTarget->GetWindowWidth() * 2);
		scissorrect.bottom = static_cast<LONG>(m_renderTarget->GetWindowHeight() * 2);
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->RSSetScissorRects(1, &scissorrect);

		//	描画終了～☆
		{
			CD3DX12_RESOURCE_BARRIER tmp = CD3DX12_RESOURCE_BARRIER::Transition(m_swapChain.GetBackBuffer().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);	//	リソースバリアをの設定をすべてに使用可能にするよ☆
			m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ResourceBarrier(1, &tmp);
		}
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->Close();
	}
}

void Crown::RenderEngine::GPUThreadsSetup()
{
	//	コマンドリストとコマンドキューの生成☆
	m_gpuThread.Initialize(m_device.Get());
	for (unsigned int i = 0; i < static_cast<unsigned int>(CommandListNames::Num); ++i)
	{
		m_commandLists.emplace_back(new CommandList(m_device.Get(),10));
		m_commandLists.back()->GetCommandList()->Close();
	}

	m_gpuThread.GPUWait(m_resourceManager->GetCopyEndWaitInfo(),1);
	m_gpuThread.SetCommandList(m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)].get(), 1);
}