#include "Vertices.h"
#include "./../DirectX12Wraps/ResourceUploader.h"
#include "d3dx12.h"

Crown::RenderObject::Vertices::Vertices()
	:
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_vertexBufferView(),
	m_indexBufferView()
{
}

Crown::RenderObject::Vertices::~Vertices()
{
}

void Crown::RenderObject::Vertices::CreateBuffer(ID3D12Device* device, std::vector<VerticesData>& vertices, std::vector<unsigned int>& indexBuffer)
{
	D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceUploader::GetInstance()->Get255AlignmentSize<VerticesData>(static_cast<unsigned int>(vertices.size())));
	device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_vertexBuffer));
	ResourceUploader::GetInstance()->UploadData<VerticesData>(m_vertexBuffer.Get(), ResourceUploader::GetInstance()->Get255AlignmentSize<VerticesData>(static_cast<unsigned int>(vertices.size())), [&](VerticesData* map)
		{
			std::copy(vertices.begin(), vertices.end(), map);
		});

	//	バッファの状態を定義するよ☆
	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.SizeInBytes = static_cast<UINT>(ResourceUploader::GetInstance()->Get255AlignmentSize<VerticesData>(static_cast<unsigned int>(vertices.size())));
	m_vertexBufferView.StrideInBytes = sizeof(VerticesData);


	heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceUploader::GetInstance()->Get255AlignmentSize<unsigned int>(static_cast<unsigned int>(indexBuffer.size())));
	device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_indexBuffer));
	ResourceUploader::GetInstance()->UploadData<unsigned int>(m_indexBuffer.Get(), ResourceUploader::GetInstance()->Get255AlignmentSize<unsigned int>(static_cast<unsigned int>(indexBuffer.size())), [&](unsigned int* map)
		{
			std::copy(indexBuffer.begin(), indexBuffer.end(), map);
		});

	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_indexBufferView.SizeInBytes = static_cast<UINT>(ResourceUploader::GetInstance()->Get255AlignmentSize<unsigned int>(static_cast<unsigned int>(indexBuffer.size())));


	m_vertexBuffer->SetName(L"vertexBuffer");
	m_indexBuffer->SetName(L"indexBuffer");
}