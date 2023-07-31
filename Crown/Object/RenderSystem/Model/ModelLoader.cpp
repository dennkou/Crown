#include "ModelLoader.h"
#include "./Vertices.h"
#include <vector>
#include <string>
#include "d3dx12.h"
#include "./../DirectX12Wraps/ResourceUploader.h"
#include "./FileType/Pmd.h"



Crown::RenderObject::Model::ModelLoader::ModelLoader(const std::wstring& fileName, LoadFile loadMode, Model& model)
	:
	m_filePath(fileName),
	m_loadMode(loadMode),
	m_model(model)
{
}

Crown::RenderObject::Model::ModelLoader::~ModelLoader()
{

}

void Crown::RenderObject::Model::ModelLoader::Load(ID3D12Device* device, TextureBuffer* textureBuffer)
{
	if (m_model.m_resource.Get() == nullptr)	//	モデルデータ用のバッファがなければ作成☆
	{
		D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceUploader::GetInstance()->Get255AlignmentSize<Model::ModelData>());
		device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_model.m_resource));
		m_model.DataUpload();

		//	ディスクリプタの作成を行うよ☆
		D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferViewDesc = {};
		constantBufferViewDesc.BufferLocation = m_model.m_resource->GetGPUVirtualAddress();
		constantBufferViewDesc.SizeInBytes = static_cast<UINT>(ResourceUploader::GetInstance()->Get255AlignmentSize<Model::ModelData>());
		m_model.m_descriptorOffset = DescriptorHeaps::GetInstance().CreateConstantBufferView(constantBufferViewDesc);
	}
	switch (m_loadMode)
	{
		case Crown::RenderObject::Model::ModelLoader::LoadFile::PMD:
			Pmd::Load(device, m_filePath, *textureBuffer, m_model.m_vertices, m_model.m_materialMeshs, m_model.m_descriptorOffset, m_model.m_resource);
			break;
		case Crown::RenderObject::Model::ModelLoader::LoadFile::PMX:
			//LoadPMX(device, textureBuffer);
			break;
		default:
			__assume(0);
			break;
	}
}