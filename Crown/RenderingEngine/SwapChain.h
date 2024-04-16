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
		const unsigned int									RTVSIZE;																			//	�����_�[�^�[�Q�b�g�r���[�̃T�C�Y���恙

		UINT												m_backBufferCount;																	//	�o�b�N�o�b�t�@�[�̐����恙
		UINT												m_backBufferIndex;																	//	�o�b�N�o�b�t�@�[�̃C���f�b�N�X���恙

		Microsoft::WRL::ComPtr<IDXGISwapChain4>				m_swapchain;																		//	�X���b�v�`�F�[�����恙
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_rtvHeaps;																			//	�����_�[�^�[�Q�b�g�r���[�̃q�[�v�̈悾�恙
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>	m_backBuffers;																		//	�����_�[�^�[�Q�b�g�q�[�v���恙�o�b�N�o�b�t�@�[�ƍ��킳���Ă���恙
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_dsvHeap;																			//	�f�v�X�X�e���V���q�[�v���恙
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_depthBuffer;																		//	�f�v�X�X�e���V���o�b�t�@�[���恙
	};
}