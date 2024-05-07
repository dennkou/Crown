#include "RenderEngine.h"

Crown::RenderEngine::RenderEngine(Window* renderTarget)
{
	m_renderTarget = renderTarget;
	//	�f�o�b�N���C���[���N������恙
	{
#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug> debugLayer;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
		debugLayer->EnableDebugLayer();
#endif // _DEBUG
	}
	//	device�̍쐬���s���恙
	{
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

		//	DXGIFactory���쐬����恙
		Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory = nullptr;
		CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgiFactory));

		//	GPU��񋓂���dGPU��T���恙
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
		//	Direct3D�f�o�C�X�̏��������恙
		D3D12CreateDevice(selectAdapter.Get(), level, IID_PPV_ARGS(&m_device));		//	D3D12Device�̍쐬���恙
	}

	m_resourceManager.reset(new ResourceManager(m_device));
	GPUThreadsSetup();
	m_swapChain.Initialize(m_device.Get(), renderTarget, m_gpuThread.GetCommandQueue().Get(), BackBufferNum);

}

Crown::RenderEngine::~RenderEngine()
{
	//	�S�X���b�h��ҋ@����恙
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
		//	�`��J�n��
		{
			CD3DX12_RESOURCE_BARRIER tmp = CD3DX12_RESOURCE_BARRIER::Transition(m_swapChain.GetBackBuffer().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);	//	���\�[�X�o���A���̐ݒ�����ׂĂɎg�p�\����`���Ƃ��Ďg�p�ɐ؂�ւ���恙
			m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ResourceBarrier(1, &tmp);																									//	���\�[�X�o���A�̐ݒ�ύX��v������恙
		}
		//	�`��Ώۂ̌��聙
		D3D12_CPU_DESCRIPTOR_HANDLE rtvH = m_swapChain.GetRenderTargetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvH.ptr += static_cast<SIZE_T>(m_swapChain.GetBackBufferIndex()) * m_swapChain.GetRenderTargetViewSize();
		const D3D12_CPU_DESCRIPTOR_HANDLE CPU_DESCRIPTOR_HANDLE = m_swapChain.GetDepthStencilDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();

		//	��ʂ���������
		float clearColor[4]{ 0,1,1,1 };
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ClearDepthStencilView(CPU_DESCRIPTOR_HANDLE, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &CPU_DESCRIPTOR_HANDLE);																	//	�����_�[�^�[�Q�b�g���w�肷��恙

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

		//	�`��I���`��
		{
			CD3DX12_RESOURCE_BARRIER tmp = CD3DX12_RESOURCE_BARRIER::Transition(m_swapChain.GetBackBuffer().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);	//	���\�[�X�o���A���̐ݒ�����ׂĂɎg�p�\�ɂ���恙
			m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->ResourceBarrier(1, &tmp);
		}
		m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)]->GetCommandList()->Close();
	}
}

void Crown::RenderEngine::GPUThreadsSetup()
{
	//	�R�}���h���X�g�ƃR�}���h�L���[�̐�����
	m_gpuThread.Initialize(m_device.Get());
	for (unsigned int i = 0; i < static_cast<unsigned int>(CommandListNames::Num); ++i)
	{
		m_commandLists.emplace_back(new CommandList(m_device.Get(),10));
		m_commandLists.back()->GetCommandList()->Close();
	}

	m_gpuThread.GPUWait(m_resourceManager->GetCopyEndWaitInfo(),1);
	m_gpuThread.SetCommandList(m_commandLists[static_cast<unsigned int>(CommandListNames::DrawMainWindow)].get(), 1);
}