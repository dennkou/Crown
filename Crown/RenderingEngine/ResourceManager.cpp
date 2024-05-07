#include "ResourceManager.h"

Crown::ResourceManager::ResourceManager(Microsoft::WRL::ComPtr<ID3D12Device> device)
	:
	m_device(device),
	m_copyCommandList(device, BUFFER_NUM, D3D12_COMMAND_LIST_TYPE_COPY),
	m_copyThread(),
	m_deleteQueueIndex(0)
{
	m_copyThread.Initialize(device, D3D12_COMMAND_LIST_TYPE_COPY);
	m_deleteQueue.resize(BUFFER_NUM);
	m_copyCommandList.SetName(L"copy");

	m_copyThread.SetCommandList(&m_copyCommandList, 1);
}

Crown::ResourceManager::~ResourceManager()
{
	m_copyCommandList.GetCommandList()->Close();
	m_copyThread.Executon();
	m_copyThread.CPUWait();
	m_copyCommandList.Reset();
}

void Crown::ResourceManager::Create(const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS HeapFlags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, const D3D12_CLEAR_VALUE* pOptimizedClearValue, Microsoft::WRL::ComPtr<ID3D12Resource>& resource)
{
	m_device->CreateCommittedResource(pHeapProperties, HeapFlags, pDesc, InitialResourceState, pOptimizedClearValue, IID_PPV_ARGS(resource.GetAddressOf()));
}

void Crown::ResourceManager::CopyExecuton()
{
	if (!m_copyThread.IsEnd())
	{
		return;
	}

	m_copyCommandList.GetCommandList()->Close();
	m_copyThread.Executon();
	m_copyCommandList.Reset();
	++m_deleteQueueIndex;
	m_deleteQueueIndex %= BUFFER_NUM;
	m_deleteQueue[m_deleteQueueIndex].clear();
}