#include "CommandList.h"

Crown::CommandList::CommandList(Microsoft::WRL::ComPtr<ID3D12Device> device)
{
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_commandAllocator.GetAddressOf()));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(m_commandList.GetAddressOf()));
}

Crown::CommandList::~CommandList()
{
}

void Crown::CommandList::Reset()
{
	m_commandAllocator->Reset();
	m_commandList->Reset(m_commandAllocator.Get(), nullptr);
}