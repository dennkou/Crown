#include "SetIndexBuffer.h"

Crown::RenderObject::RenderCommand::SetIndexBuffer::SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView, Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer)
	:
	m_indexBufferView(indexBufferView),
	m_indexBuffer(indexBuffer)
{
}

Crown::RenderObject::RenderCommand::SetIndexBuffer::~SetIndexBuffer()
{
}

void Crown::RenderObject::RenderCommand::SetIndexBuffer::Load(FILE* file)
{
}

void Crown::RenderObject::RenderCommand::SetIndexBuffer::Write(FILE* file)
{
}

void Crown::RenderObject::RenderCommand::SetIndexBuffer::Run(GraphicsCommandList& commandList)
{
	commandList.GetGraphicsCommandList()->IASetIndexBuffer(m_indexBufferView);
	commandList.LockResource(m_indexBuffer);
}