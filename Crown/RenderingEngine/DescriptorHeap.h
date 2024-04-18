#pragma once
#include "DirectX12.h"

namespace Crown
{
	//	ディスクリプタヒープをラップしたクラスだよ☆	ディスクリプタの並びも決定するよ☆
	class DescriptorHeap
	{
	public:
		DescriptorHeap(Microsoft::WRL::ComPtr<ID3D12Device> device);
		~DescriptorHeap();

		void RenderUpdate();		//	

		inline Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() noexcept { return m_gpuDescriptorHeap; }
		inline Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature() noexcept { return m_rootSignature; }
	private:
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_gpuDescriptorHeap;
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;


	};
}