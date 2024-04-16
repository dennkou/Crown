#pragma once
#include "Crown.h"
#include "DirectX12.h"
#include <vector>

namespace Crown
{
	class SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		void Initialize(ID3D12Device* device, const Crown::Window* const window, ID3D12CommandQueue* commandQueue, unsigned int bufferNum = 2);

		void Present(UINT syncInterval);

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetRenderTargetDescriptorHeap() const noexcept { return m_rtvHeaps; }
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDepthStencilDescriptorHeap() const noexcept { return m_dsvHeap; }
		Microsoft::WRL::ComPtr<ID3D12Resource> GetBackBuffer() const noexcept { return m_backBuffers[m_backBufferIndex]; }
		unsigned int GetBackBufferIndex() const noexcept { return m_backBufferIndex; }
		inline unsigned int GetRenderTargetViewSize() const noexcept { return RTVSIZE; }
	private:
		const unsigned int									RTVSIZE;																			//	レンダーターゲットビューのサイズだよ☆

		UINT												m_backBufferCount;																	//	バックバッファーの数だよ☆
		UINT												m_backBufferIndex;																	//	バックバッファーのインデックスだよ☆

		Microsoft::WRL::ComPtr<IDXGISwapChain4>				m_swapchain;																		//	スワップチェーンだよ☆
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_rtvHeaps;																			//	レンダーターゲットビューのヒープ領域だよ☆
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>	m_backBuffers;																		//	レンダーターゲットヒープだよ☆バックバッファーと合わさっているよ☆
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_dsvHeap;																			//	デプスステンシルヒープだよ☆
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_depthBuffer;																		//	デプスステンシルバッファーだよ☆
	};
}