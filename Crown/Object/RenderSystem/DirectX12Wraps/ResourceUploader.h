#pragma once
#ifndef CROWN_RENDEROBJECT_RESOURCE
#define CROWN_RENDEROBJECT_RESOURCE
#include <vector>
#include <d3d12.h>
#include "d3dx12.h"
#include "GraphicsCommandList.h"
#include <functional>
#include <wrl.h>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/28
		// 作成者 : 服部颯澄
		// 
		// ID3D12Resourceの各種操作をラップしたものだよ☆
		// 
		//================================================
		class ResourceUploader
		{
		public:
			static void CreateResourceUploader(ID3D12Device* device, GraphicsCommandList* commandList);
			static ResourceUploader* GetInstance();
			static void DeleteInstance();

			/// <summary>
			/// 指定されたバッファーにデータをアップロードするよ☆
			/// </summary>
			/// <typeparam name="DataType"></typeparam>
			/// <param name="uploadTarget"></param>
			/// <param name="dataNum"></param>
			/// <param name="map"></param>
			template<typename DataType>
			void UploadData(ID3D12Resource* uploadTarget, UINT64 dataNum, std::function<void(DataType*)> dataCopy);

			template<typename DataType>
			UINT64 Get255AlignmentSize(unsigned int size = 1) { return static_cast<UINT64>(((sizeof(DataType) * size) + 0xff) & ~0xff); }

			/// <summary>
			/// アップロードに使用したバッファーを開放するよ☆
			/// </summary>
			void DeleteUploadResource();
		private:
			ResourceUploader();
			~ResourceUploader();

			ResourceUploader(ResourceUploader& resourceUploader) = delete;
			ResourceUploader& operator=(ResourceUploader& resourceUploader) = delete;

			static ResourceUploader* me;

			ID3D12Device* m_device;
			GraphicsCommandList* m_commandList;
			std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> uploadResource[2];
			unsigned int m_bufferIndex;
		};

		template<typename DataType>
		inline void ResourceUploader::UploadData(ID3D12Resource* uploadTarget, UINT64 dataSize, std::function<void(DataType*)> dataCopy)
		{
			Microsoft::WRL::ComPtr<ID3D12Resource> upload = nullptr;
			D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(dataSize);
			m_device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&upload));
			upload->SetName(L"UploadBuffer");
			DataType* map = nullptr;
			upload->Map(0, nullptr, (void**)&map);
			dataCopy(map);
			upload->Unmap(0, nullptr);

			m_commandList->GetCopyCommandList()->CopyBufferRegion(uploadTarget, 0, upload.Get(), 0, dataSize);
			uploadResource[m_bufferIndex].emplace_back(upload);
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RESOURCE