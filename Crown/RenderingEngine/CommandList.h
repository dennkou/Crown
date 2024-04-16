#pragma once
#include "DirectX12.h"

namespace Crown
{
	class CommandList
	{
	public:
		CommandList(Microsoft::WRL::ComPtr<ID3D12Device> device);
		~CommandList();

		void Reset();

		inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList() const noexcept { return m_commandList; }
	private:
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	};
}