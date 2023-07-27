#include "SetDescriptor.h"
#include "./../DirectX12Wraps/DescriptorHeaps.h"

Crown::RenderObject::RenderCommand::SetDescriptor::SetDescriptor(unsigned int descriptorOffset, unsigned int rootParameterIndex)
	:
	m_offset(descriptorOffset),
	m_rootParameterIndex(rootParameterIndex)
{
}

Crown::RenderObject::RenderCommand::SetDescriptor::~SetDescriptor()
{

}

void Crown::RenderObject::RenderCommand::SetDescriptor::Load(FILE* file)
{
	fread(&m_rootParameterIndex, sizeof(unsigned int), 1, file);
	fread(&m_offset, sizeof(unsigned int), 1, file);
}

void Crown::RenderObject::RenderCommand::SetDescriptor::Write(FILE* file)
{
	fwrite(&m_rootParameterIndex, sizeof(unsigned int), 1, file);
	fwrite(&m_offset, sizeof(unsigned int), 1, file);
}

void Crown::RenderObject::RenderCommand::SetDescriptor::Run(ID3D12GraphicsCommandList* commandList)
{
	commandList->SetGraphicsRootDescriptorTable(m_rootParameterIndex, DescriptorHeaps::GetInstance().GetHandle(m_offset));
}