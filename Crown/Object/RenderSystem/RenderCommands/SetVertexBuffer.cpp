#include "SetVertexBuffer.h"

Crown::RenderObject::RenderCommand::SetVertexBuffer::SetVertexBuffer(UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView)
	:
	m_startSlot(startSlot),
	m_numViews(numViews),
	m_vertexBufferView(vertexBufferView)
{
}

Crown::RenderObject::RenderCommand::SetVertexBuffer::~SetVertexBuffer()
{
}

void Crown::RenderObject::RenderCommand::SetVertexBuffer::Load(FILE* file)
{
}

void Crown::RenderObject::RenderCommand::SetVertexBuffer::Write(FILE* file)
{
}

void Crown::RenderObject::RenderCommand::SetVertexBuffer::Run(ID3D12GraphicsCommandList* commandList)
{
	commandList->IASetVertexBuffers(m_startSlot, m_numViews, m_vertexBufferView);
}
