#include "MaterialMesh.h"

Crown::RenderObject::MaterialMesh::MaterialMesh(unsigned int indexNum, unsigned int m_indexOffset)
	:
	m_indexNum(indexNum),
	m_indexOffset(m_indexOffset),
	m_materials(static_cast<int>(MaterialTag::Num))
{
}

Crown::RenderObject::MaterialMesh::~MaterialMesh()
{
}

void Crown::RenderObject::MaterialMesh::Draw(MaterialTag drawTag, GraphicsCommandList& commandList)
{
	m_materials[static_cast<int>(drawTag)].Draw(commandList);
	commandList.GetGraphicsCommandList()->DrawIndexedInstanced(m_indexNum, 1, m_indexOffset, 0, 0);
}