#include "SetVertexBuffer.h"

Crown::RenderObject::RenderCommand::SetVertexBuffer::SetVertexBuffer(UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView, Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer)
	:
	m_startSlot(startSlot),
	m_numViews(numViews),
	m_vertexBufferView(vertexBufferView),
	m_vertexBuffer(vertexBuffer)
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

void Crown::RenderObject::RenderCommand::SetVertexBuffer::Run(GraphicsCommandList& commandList)
{
	commandList.GetGraphicsCommandList()->IASetVertexBuffers(m_startSlot, m_numViews, m_vertexBufferView);
	commandList.LockResource(m_vertexBuffer);
}
