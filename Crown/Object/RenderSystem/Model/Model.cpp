#include "Model.h"
#include "./../../../System.h"
#include "ModelLoader.h"

Crown::RenderObject::Model::Model()
	:
	m_position(),
	m_rotate(),
	m_materialMeshs()
{
	System::GetInstance().GetRenderSystem().GetModelManager().AddModel(this);
}

Crown::RenderObject::Model::Model(const Model& model)
	:
	m_position(),
	m_rotate(),
	m_materialMeshs()
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

void Crown::RenderObject::Model::Draw(MaterialTag drawTag, GraphicsCommandList& commandList)
{
	for (MaterialMesh& materialMesh : m_materialMeshs)
	{
		materialMesh.Draw(drawTag, commandList);
	}
}