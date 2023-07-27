#include "ModelManager.h"
#include "Model.h"
#include "ModelLoader.h"

Crown::RenderObject::ModelManager::ModelManager()
	:
	m_device(),
	m_textureBuffer()
{
}

Crown::RenderObject::ModelManager::~ModelManager()
{
}

void Crown::RenderObject::ModelManager::Initialize(ID3D12Device* device, TextureBuffer* textureBuffer)
{
	m_device = device;
	m_textureBuffer = textureBuffer;
}

void Crown::RenderObject::ModelManager::AddModel(Model* newModel)
{
	m_models.push_back(newModel);
}

void Crown::RenderObject::ModelManager::DeleteModel(Model* deleteModel)
{
	for (int i = 0, size = static_cast<int>(m_models.size()); i < size; ++i)
	{
		if (m_models[i] == deleteModel) 
		{
			m_models.erase(m_models.begin() + i);
		}
	}
}

void Crown::RenderObject::ModelManager::Draw(MaterialTag drawTag, GraphicsCommandList& commandList)
{
	for (Model* model : m_models)
	{
		model->Draw(drawTag, commandList);
	}
}

void Crown::RenderObject::ModelManager::loadModel(Model::ModelLoader* modelLoader)
{
	modelLoader->Load(m_device, m_textureBuffer);
}