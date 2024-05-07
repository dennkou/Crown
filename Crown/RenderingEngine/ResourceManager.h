#pragma once
#include <vector>
#include "DirectX12.h"
#include <functional>

#include "CommandList.h"
#include "GPUThread.h"

namespace Crown
{
	class ResourceManager
	{
	public:
		ResourceManager(Microsoft::WRL::ComPtr<ID3D12Device> device);
		~ResourceManager();
		
		void Create(const D3D12_HEAP_PROPERTIES* pHeapProperties, D3D12_HEAP_FLAGS HeapFlags, const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, const D3D12_CLEAR_VALUE* pOptimizedClearValue, Microsoft::WRL::ComPtr<ID3D12Resource>& resource);

		template<class DataType>
		void Upload(Microsoft::WRL::ComPtr<ID3D12Resource>& uploadTarget, unsigned long long dataSize, std::function<void(DataType*)> dataCopy)
		{
			Microsoft::WRL::ComPtr<ID3D12Resource> upload = nullptr;
			D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(dataSize);
			Create(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, upload);
			upload->SetName(L"UploadBuffer");
			DataType* map = nullptr;
			upload->Map(0, nullptr, (void**)&map);
			dataCopy(map);
			upload->Unmap(0, nullptr);

			m_copyCommandList.GetCommandList()->CopyBufferRegion(uploadTarget.Get(), 0, upload.Get(), 0, dataSize);
			Delete(upload);
		}

		inline void Delete(Microsoft::WRL::ComPtr<ID3D12Resource> deleteResource) noexcept
		{
			m_deleteQueue[GetDeleteWaitingQueue()].push_back(deleteResource);
		}

		//	コピーを実行するよ☆
		void CopyExecuton();

		template<typename DataType>
		inline static UINT64 Get255AlignmentSize(unsigned int size = 1) noexcept { return static_cast<UINT64>(((sizeof(DataType) * size) + 0xff) & ~0xff); }

		GPUThread::WaitInfo GetCopyEndWaitInfo() { return m_copyThread.GetExecutonPhaseWaitInfo(1); }
	private:
		unsigned int GetDeleteWaitingQueue() const noexcept { return (m_deleteQueueIndex + 1) % BUFFER_NUM; }

		static constexpr unsigned int BUFFER_NUM = 2;

		std::vector<std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>> m_deleteQueue;
		unsigned int m_deleteQueueIndex;
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;

		CommandList m_copyCommandList;
		GPUThread m_copyThread;
	};
}