#pragma once
#include <vector>
#include "DirectX12.h"

namespace Crown
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		
		void Create(const D3D12_RESOURCE_DESC* pDesc, D3D12_RESOURCE_STATES InitialResourceState, const D3D12_CLEAR_VALUE* pOptimizedClearValue, Microsoft::WRL::ComPtr<ID3D12Resource> resource);

	private:
		bool m_upload;													//	GPUにアップロードするリソースがある？☆
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_deleteQueue;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_uploadCommandList;
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;
	};
}