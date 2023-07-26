#pragma once
#ifndef CROWN_RENDEROBJECT_DESCRIPTORHEAPS
#define CROWN_RENDEROBJECT_DESCRIPTORHEAPS
#include <d3d12.h>
#include <wrl.h>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/28
		// 作成者 : 服部颯澄
		// 
		// ディスクリプタヒープの管理を行うクラスだよ☆
		// 追加は可能だけど削除は想定してないよ☆
		// 
		//================================================
		class DescriptorHeaps
		{
		public:

			static void CreateDescriptorHeaps(ID3D12Device* device, unsigned int heapsSize = 65535);
			static DescriptorHeaps& GetInstance();
			static void DeleteDescriptorHeaps();

			/// <summary>
			/// 管理しているディスクリプタヒープにコンスタントバッファビューを追加するよ☆
			/// </summary>
			/// <param name="constantBufferViewDesc">作成するコンスタントバッファビュー☆</param>
			/// <returns>ディスクリプタのオフセット位置☆</returns>
			unsigned int CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC& constantBufferViewDesc);

			/// <summary>
			/// 管理しているディスクリプタヒープにシェーダーリソースビューを追加するよ☆
			/// </summary>
			/// <param name="resource">シェーダーリソースビューが参照するリソース☆</param>
			/// <param name="shaderResourceViewDesc">作成するシェーダーリソースビュー☆</param>
			/// <returns>ディスクリプタのオフセット位置☆</returns>
			unsigned int CreateShaderResourceView(ID3D12Resource* resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& shaderResourceViewDesc);

			/// <summary>
			/// 指定位置のGPUハンドルを取得するよ☆
			/// </summary>
			/// <returns></returns>
			D3D12_GPU_DESCRIPTOR_HANDLE GetHandle(unsigned int offset) const;

			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			bool GetResetDescriptorHeapFlag() const noexcept { return m_changeSize; }

			void ResetDescriptorHeapFlag()noexcept { m_changeSize = false; }

			inline ID3D12DescriptorHeap* GetDescriptorHeap() const { return m_descriptorHeap[m_index].Get(); }

		private:
			DescriptorHeaps();
			~DescriptorHeaps();
			DescriptorHeaps(DescriptorHeaps& DescriptorHeaps) = delete;
			DescriptorHeaps& operator=(DescriptorHeaps& DescriptorHeaps) = delete;
			static DescriptorHeaps* me;

			/// <summary>
			/// 新しくディスクリプタ用のヒープ領域を確保して、確保した位置を返すよ☆
			/// </summary>
			/// <returns></returns>
			D3D12_CPU_DESCRIPTOR_HANDLE CreateDescriptor();

			/// <summary>
			/// ディスクリプタヒープを生成するよ☆
			/// </summary>
			/// <param name="flags"></param>
			/// <param name="NumDescriptors"></param>
			/// <param name="descriptorHeap"></param>
			void CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_FLAGS flags,UINT NumDescriptors,ID3D12DescriptorHeap** descriptorHeap);

			/// <summary>
			/// CPU用ディスクリプタヒープをGPU用のディスクリプタヒープにアップロードするよ☆
			/// </summary>
			void UploadDescriptorHeap();



			ID3D12Device* m_device;												//	ヒープの作成に使用するデバイスだよ☆
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_cpuDescriptorHeap;	//	シェーダー側から認識されないディスクリプタヒープだよ☆
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptorHeap[2];	//	シェーダー側から認識されるディスクリプタヒープだよ☆
			const UINT DESCRIPTOR_HANDLE_INCREMENT_SIZE;						//	ディスクリプタのサイズだよ☆
			unsigned int m_index;												//	現在使用しているディスクリプタヒープだよ☆
			unsigned int m_descriptorNum;										//	現在のディスクリプタ数だよ☆
			unsigned int m_maxDescriptorNum;									//	ディスクリプタの最大数だよ☆
			bool m_changeSize;													//	最大サイズを変更したのフラグだよ☆
		};
	}
}
#endif // !CROWN_RENDEROBJECT_DESCRIPTORHEAPS