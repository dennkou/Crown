#pragma once
#include "RenderEngine.h"

namespace Crown
{
	class BundleCommandList
	{
	public:
		BundleCommandList(Microsoft::WRL::ComPtr<ID3D12Device> device, Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState);
		~BundleCommandList();

		void Reset(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator) noexcept;

		inline Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetBundleCommandList() const noexcept { return m_commandList.Get(); }
		inline Microsoft::WRL::ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const noexcept { return m_commandAllocator.Get(); }
	private:
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
	};
}