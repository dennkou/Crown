#include "SetDescriptor.h"
#include "./../DirectX12Wraps/DescriptorHeaps.h"

Crown::RenderObject::RenderCommand::SetDescriptor::SetDescriptor(unsigned int descriptorOffset, unsigned int rootParameterIndex, const Microsoft::WRL::ComPtr<ID3D12Resource>& useResource)
	:
	m_offset(descriptorOffset),
	m_rootParameterIndex(rootParameterIndex),
	m_useResource(useResource)
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

void Crown::RenderObject::RenderCommand::SetDescriptor::Run(GraphicsCommandList& commandList)
{
	commandList.GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(m_rootParameterIndex, DescriptorHeaps::GetInstance().GetHandle(m_offset));
	commandList.LockResource(m_useResource);
}