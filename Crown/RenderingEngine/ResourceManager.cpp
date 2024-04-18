#include "ResourceManager.h"

Crown::ResourceManager::ResourceManager(Microsoft::WRL::ComPtr<ID3D12Device> device, std::shared_ptr<CommandList> copyCommandList)
	:
	m_device(device),
	m_copyCommandList(copyCommandList),
	m_deleteQueueIndex(0)
{
	copyCommandList->Reset();
	copyCommandList->GetCommandList()->SetName(L"Ç±Ç“Å[ÇÊÅ[Ç±Ç‹ÇÒÇ«ÇËÇ∑Ç∆");
}

Crown::ResourceManager::~ResourceManager()
{
}

void Crown::ResourceManager::Create(const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS HeapFlags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, const D3D12_CLEAR_VALUE* pOptimizedClearValue, Microsoft::WRL::ComPtr<ID3D12Resource>& resource)
{
	m_device->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState, pOptimizedClearValue, IID_PPV_ARGS(resource.GetAddressOf()));
}

void Crown::ResourceManager::Close()
{
	m_copyCommandList->GetCommandList()->Close();
}

void Crown::ResourceManager::CopyExecuton()
{
	m_copyCommandList->Reset();
	m_deleteQueue[m_deleteQueueIndex].clear();
}