#include "BlobConstBuffer.h"
#include <DirectXMath.h>
#include <d3dx12.h>
#include "./../DirectX12Wraps/ResourceUploader.h"
#include "./../DirectX12Wraps/DescriptorHeaps.h"

Crown::RenderObject::BlobConstBuffer::BlobConstBuffer(std::vector<DataType>& dataTypeDescriptor, ID3D12Device* device)
	:
	m_dataTypeDescriptor(dataTypeDescriptor)
{
	size_t bufferSize = 0;
	for (const DataType& dataType : dataTypeDescriptor)
	{
		bufferSize += DATA_SIZE[static_cast<unsigned char>(dataType)];
	}
	m_constantBufferData = std::vector<byte>(bufferSize);

	//	バッファの作成を行うよ☆
	D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceUploader::GetInstance()->Get255AlignmentSize<byte>(static_cast<unsigned int>(bufferSize)));
	device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_constantBuffer));

	//	ディスクリプタの作成を行うよ☆
	D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferViewDesc = {};
	constantBufferViewDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
	constantBufferViewDesc.SizeInBytes = static_cast<UINT>(ResourceUploader::GetInstance()->Get255AlignmentSize<byte>(static_cast<unsigned int>(bufferSize)));
	m_descriptorOffset = DescriptorHeaps::GetInstance().CreateConstantBufferView(constantBufferViewDesc);
}

Crown::RenderObject::BlobConstBuffer::~BlobConstBuffer()
{
	m_constantBufferData.clear();
	m_dataTypeDescriptor.clear();
}

byte* Crown::RenderObject::BlobConstBuffer::GetDataPointer(unsigned int parameterIndex)
{
	unsigned int bufferIndex = 0;
	for (unsigned int i = 0; i < parameterIndex; ++i)
	{
		bufferIndex += static_cast<unsigned int>(DATA_SIZE[static_cast<unsigned char>(m_dataTypeDescriptor[i])]);
	}
	return &m_constantBufferData[bufferIndex];
}

void Crown::RenderObject::BlobConstBuffer::UploadConstantBuffer()
{
	ResourceUploader::GetInstance()->UploadData<byte>(m_constantBuffer.Get(), ResourceUploader::GetInstance()->Get255AlignmentSize<byte>(static_cast<unsigned int>(m_constantBufferData.size())), [&](byte* mapPointer)
		{
			for (unsigned int i = 0, size = static_cast<unsigned int>(m_constantBufferData.size()); i < size; ++i)
			{
				mapPointer[i] = m_constantBufferData[i];
			}
		});
}
