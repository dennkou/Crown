#include "BundleCommandList.h"

Crown::BundleCommandList::BundleCommandList(Microsoft::WRL::ComPtr<ID3D12Device> device, Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState)
{
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_BUNDLE, IID_PPV_ARGS(&m_commandAllocator));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_BUNDLE, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_commandList));
}

Crown::BundleCommandList::~BundleCommandList()
{

}

void Crown::BundleCommandList::Reset(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator) noexcept
{
	m_commandAllocator = commandAllocator;
	m_commandList->Reset(m_commandAllocator.Get(), m_pipelineState.Get());
}