#pragma once
#include <memory>
#include <functional>
#include "DirectX12.h"
#include "ResourceManager.h"

namespace Crown
{
	class Resource
	{
	public:
		Resource(std::shared_ptr<ResourceManager> resourceManager);
		~Resource();

		template<typename DataType>
		void Upload(std::function<void(Microsoft::WRL::ComPtr<ID3D12Resource>, DataType*)> dataCopy)
		{

		}

		inline operator Microsoft::WRL::ComPtr<ID3D12Resource>() noexcept
		{
			return m_resource;
		}
	private:
		std::shared_ptr<ResourceManager> m_resourceManager;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_resource;
	};
}