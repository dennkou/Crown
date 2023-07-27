#include "SetIndexBuffer.h"

Crown::RenderObject::RenderCommand::SetIndexBuffer::SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView)
	:
	m_indexBufferView(indexBufferView)
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

void Crown::RenderObject::RenderCommand::SetIndexBuffer::Run(ID3D12GraphicsCommandList* commandList)
{
	commandList->IASetIndexBuffer(m_indexBufferView);
}