#pragma once
#include "DirectX12.h"
#include <vector>

namespace Crown
{
	class CommandList
	{
	public:
		CommandList(Microsoft::WRL::ComPtr<ID3D12Device> device, unsigned int allocatorNum = 2);
		~CommandList();

		void Reset();

		inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList() const noexcept { return m_commandList; }
	private:
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> m_commandAllocators;
		unsigned int m_allocatorIndex;
	};
}