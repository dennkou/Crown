#include "Model.h"
#include "./../../../System.h"
#include "ModelLoader.h"
#include "./../DirectX12Wraps/ResourceUploader.h"

Crown::RenderObject::Model::Model()
	:
	m_position(),
	m_rotate(),
	m_materialMeshs(),
	m_descriptorOffset(0)
{
	System::GetInstance().GetRenderSystem().GetModelManager().AddModel(this);
}

Crown::RenderObject::Model::Model(const Model& model)
	:
	m_position(DirectX::XMFLOAT3(0, 0, 0)),
	m_rotate(DirectX::XMFLOAT3(0, 0, 0)),
	m_materialMeshs(),
	m_descriptorOffset(0)
{
	System::GetInstance().GetRenderSystem().GetModelManager().AddModel(this);
}

Crown::RenderObject::Model::~Model()
{
	System::GetInstance().GetRenderSystem().GetModelManager().DeleteModel(this);
}



void Crown::RenderObject::Model::LoadPMD(const std::wstring& fileName)
{
	ModelLoader loader(fileName, ModelLoader::LoadFile::PMD, *this);
	System::GetInstance().GetRenderSystem().GetModelManager().loadModel(&loader);
}

void Crown::RenderObject::Model::LoadPMX(const std::wstring& fileName)
{
	ModelLoader loader(fileName, ModelLoader::LoadFile::PMX, *this);
	System::GetInstance().GetRenderSystem().GetModelManager().loadModel(&loader);
}

void Crown::RenderObject::Model::Draw(MaterialTag drawTag, GraphicsCommandList& commandList)
{
	for (MaterialMesh& materialMesh : m_materialMeshs)
	{
		materialMesh.Draw(drawTag, commandList);
	}
}

void Crown::RenderObject::Model::DataUpload()
{
	auto upload = [&](ModelData* map)
	{
		map->m_world = DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z) * DirectX::XMMatrixRotationRollPitchYaw(m_rotate.x, m_rotate.y, m_rotate.z);
		for (int i = 0; i < 255; ++i)
		{
			map->m_bone[i] = DirectX::XMMatrixIdentity();
		}
	};

	ResourceUploader::GetInstance()->UploadData<Model::ModelData>(m_resource.Get(), ResourceUploader::GetInstance()->Get255AlignmentSize<Model::ModelData>(1), upload);
}