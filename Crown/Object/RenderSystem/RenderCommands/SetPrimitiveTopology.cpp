#include "SetPrimitiveTopology.h"

Crown::RenderObject::RenderCommand::SetPrimitiveTopology::SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY primitiveTopology)
	:
	m_primitiveTopology(primitiveTopology)
{
}

Crown::RenderObject::RenderCommand::SetPrimitiveTopology::~SetPrimitiveTopology()
{
}

void Crown::RenderObject::RenderCommand::SetPrimitiveTopology::Load(FILE* file)
{
}

void Crown::RenderObject::RenderCommand::SetPrimitiveTopology::Write(FILE* file)
{
}

void Crown::RenderObject::RenderCommand::SetPrimitiveTopology::Run(GraphicsCommandList& commandList)
{
	commandList.GetGraphicsCommandList()->IASetPrimitiveTopology(m_primitiveTopology);
}