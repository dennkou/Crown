#include "SetDescriptorHeap.h"
#include "./../DirectX12Wraps/DescriptorHeaps.h"

Crown::RenderObject::RenderCommand::SetDescriptorHeap::SetDescriptorHeap()
{

}

Crown::RenderObject::RenderCommand::SetDescriptorHeap::~SetDescriptorHeap()
{

}

void Crown::RenderObject::RenderCommand::SetDescriptorHeap::Load(FILE* file)
{

}

void Crown::RenderObject::RenderCommand::SetDescriptorHeap::Write(FILE* file)
{

}

void Crown::RenderObject::RenderCommand::SetDescriptorHeap::Run(GraphicsCommandList& commandList)
{
	ID3D12DescriptorHeap* descriptorHeap = DescriptorHeaps::GetInstance().GetDescriptorHeap();
	commandList.GetGraphicsCommandList()->SetDescriptorHeaps(1, &descriptorHeap);
}