#pragma once
#include <vector>
#include "DirectX12.h"
#include <initializer_list>
#include "ResourceManager.h"

namespace Crown
{
	//class Vertices
	//{
	//public:
	//	Vertices() = default;
	//	~Vertices() = default;

	//	template<class VerticesData>
	//	void CreateBuffer(ResourceManager& resourceManager, std::vector<VerticesData>& vertices, std::vector<unsigned int>& indexBuffer, std::initializer_list<D3D12_INPUT_ELEMENT_DESC> inputLayout)
	//	{
	//		//	頂点バッファーの作成☆
	//		D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	//		D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceManager::Get255AlignmentSize<VerticesData>(static_cast<unsigned int>(vertices.size())));
	//		resourceManager.Create(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, m_vertexBuffer);
	//		resourceManager.Upload<VerticesData>(m_vertexBuffer, ResourceManager::Get255AlignmentSize<VerticesData>(static_cast<unsigned int>(vertices.size())), [&](VerticesData* map)
	//			{
	//				std::copy(vertices.begin(), vertices.end(), map);
	//			});
	//		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	//		m_vertexBufferView.SizeInBytes = static_cast<UINT>(ResourceManager::Get255AlignmentSize<VerticesData>(static_cast<unsigned int>(vertices.size())));
	//		m_vertexBufferView.StrideInBytes = sizeof(VerticesData);

	//		//	インデックスバッファーの作成☆
	//		heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	//		resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceManager::Get255AlignmentSize<unsigned int>(static_cast<unsigned int>(indexBuffer.size())));
	//		resourceManager.Create(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_indexBuffer));
	//		resourceManager.Upload<unsigned int>(m_indexBuffer, ResourceManager::Get255AlignmentSize<unsigned int>(static_cast<unsigned int>(indexBuffer.size())), [&](unsigned int* map)
	//			{
	//				std::copy(indexBuffer.begin(), indexBuffer.end(), map);
	//			});
	//		m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	//		m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	//		//m_indexBufferView.SizeInBytes = static_cast<UINT>(ResourceUploader::GetInstance()->Get255AlignmentSize<unsigned int>(static_cast<unsigned int>(indexBuffer.size())));

	//		m_vertexBuffer->SetName(L"vertexBuffer");
	//		m_indexBuffer->SetName(L"indexBuffer");

	//		m_inputLayout = inputLayout;
	//	}

	//	inline D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() { return &m_vertexBufferView; }
	//	inline const Microsoft::WRL::ComPtr<ID3D12Resource> GetConstVertexBuffer() { return m_vertexBuffer; }
	//	inline D3D12_INDEX_BUFFER_VIEW* GetIndexBufferView() { return &m_indexBufferView; }
	//	inline const Microsoft::WRL::ComPtr<ID3D12Resource> GetConstIndexBuffer() { return m_indexBuffer; }
	//private:
	//	//Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer;
	//	//D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	//	//Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBuffer;
	//	//D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

	//	//Microsoft::WRL::ComPtr<D3D12_INPUT_ELEMENT_DESC> m_inputLayout;
	//};
}