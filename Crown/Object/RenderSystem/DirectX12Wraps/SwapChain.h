#pragma once
#ifndef CROWN_RENDER_OBJECT_SWAPCHAIN
#define CROWN_RENDER_OBJECT_SWAPCHAIN

#include <dxgi1_6.h>
#include <d3d12.h>
#include <vector>
#include <wrl.h>
namespace Crown
{
	class Window;

	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/21
		// 作成者 : 服部颯澄
		// 
		// スワップチェーンをラップするクラスだよ☆
		// 
		//================================================
		class SwapChain
		{
		public:
			SwapChain();
			~SwapChain();

			/// <summary>
			/// 初期化をするよ☆
			/// </summary>
			/// <param name="dxgiFactory"></param>
			/// <param name="device"></param>
			/// <param name="window"></param>
			/// <param name="commandQueue"></param>
			/// <param name="bufferNum"></param>
			void Initialize(ID3D12Device* device, const Crown::Window* const window, ID3D12CommandQueue* commandQueue, unsigned int bufferNum = 3);

			/// <summary>
			/// スワップチェーンをフリップするよ☆
			/// </summary>
			/// <param name="syncInterval"></param>
			void Present(UINT syncInterval);

			ID3D12DescriptorHeap* GetRenderTargetDescriptorHeap() const { return m_rtvHeaps.Get(); }
			ID3D12DescriptorHeap* GetDepthStencilDescriptorHeap() const { return m_dsvHeap.Get();  }
			ID3D12Resource* GetBackBuffer() const { return m_backBuffers[m_backBufferIndex].Get(); }
			UINT GetBackBufferIndex() const { return m_backBufferIndex; }
			unsigned int GetRenderTargetViewSize() const { return RTVSIZE; }

		private:
			inline void CreateSwapChain(IDXGIFactory2* dxgiFactory, UINT hidth, UINT height, HWND windowHandle, ID3D12CommandQueue* commandQueue);	//	スワップチェーンの作成だよ☆
			inline void CreateRenderTargetView(ID3D12Device* device);																				//	レンダーターゲットビューの作成だよ☆
			inline void CreatDepthBuffer(ID3D12Device* device, UINT width, UINT height);															//	深度、ステンシルビューの作成だよ☆


			const unsigned int									RTVSIZE;																								//	レンダーターゲットビューのサイズだよ☆

			UINT												m_backBufferCount;																						//	バックバッファーの数だよ☆
			UINT												m_backBufferIndex;																						//	バックバッファーのインデックスだよ☆

			Microsoft::WRL::ComPtr<IDXGISwapChain4>				m_swapchain;																							//	スワップチェーンだよ☆

			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_rtvHeaps;																								//	レンダーターゲットビューのヒープ領域だよ☆
			std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>	m_backBuffers;																							//	レンダーターゲットヒープだよ☆バックバッファーと合わさっているよ☆

			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_dsvHeap;																								//	デプスステンシルヒープだよ☆
			Microsoft::WRL::ComPtr<ID3D12Resource>				m_depthBuffer;																							//	デプスステンシルバッファーだよ☆
		};
	}
}
#endif // !CROWN_RENDER_OBJECT_SWAPCHAIN