#include "CommandList.h"

Crown::CommandList::CommandList(Microsoft::WRL::ComPtr<ID3D12Device> device, unsigned int allocatorNum, D3D12_COMMAND_LIST_TYPE commandListType)
{
	m_allocatorIndex = 0;
	m_commandAllocators.resize(allocatorNum);
	for (unsigned int i = 0; i < allocatorNum; ++i)
	{
		device->CreateCommandAllocator(commandListType, IID_PPV_ARGS(m_commandAllocators[i].GetAddressOf()));
	}
	device->CreateCommandList(0, commandListType, m_commandAllocators[m_allocatorIndex].Get(), nullptr, IID_PPV_ARGS(m_commandList.GetAddressOf()));
}

Crown::CommandList::~CommandList()
{
}

void Crown::CommandList::Reset()
{
	++m_allocatorIndex;
	m_allocatorIndex %= static_cast<unsigned int>(m_commandAllocators.size());
	m_commandAllocators[m_allocatorIndex]->Reset();
	m_commandList->Reset(m_commandAllocators[m_allocatorIndex].Get(), nullptr);
}

void Crown::CommandList::SetName(std::wstring name)
{
	m_commandList->SetName(name.data());
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_commandAllocators.size()); ++i)
	{
		m_commandAllocators[i]->SetName((name + std::to_wstring(i)).data());
	}
}