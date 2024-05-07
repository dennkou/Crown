#pragma once
#include "DirectX12.h"
#include <vector>

namespace Crown
{
	class CommandList
	{
	public:
		CommandList(Microsoft::WRL::ComPtr<ID3D12Device> device, unsigned int allocatorNum = 2, D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT);
		~CommandList();

		void Reset();

		void SetName(std::wstring name);

		inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList() const noexcept { return m_commandList; }
	private:
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
		std::vector<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> m_commandAllocators;
		unsigned int m_allocatorIndex;
	};
}