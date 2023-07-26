#include "RenderCommandFactory.h"
#include "SetDescriptor.h"
#include "SetDescriptorHeap.h"
#include "SetRootSignature.h"
#include "SetPipelineState.h"
#include "SetVertexBuffer.h"
#include "SetIndexBuffer.h"
#include "SetPrimitiveTopology.h"

Crown::RenderObject::RenderCommand::RenderCommandFactory::RenderCommandFactory()
{
}

Crown::RenderObject::RenderCommand::RenderCommandFactory::~RenderCommandFactory()
{
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::Load(FILE* file, RenderCommandQueue& commandQueue)
{
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::Write(FILE* file, RenderCommandQueue* commandQueue)
{
}



//	Ç±Ç±Ç©ÇÁRenderCommandÇÉZÉbÉgÇ∑ÇÈä÷êîÇæÇÊÅô



void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetDescriptorHeap(RenderCommandQueue& commandQueue)
{
	commandQueue.AddCommand(new SetDescriptorHeap);
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetDescriptor(RenderCommandQueue& commandQueue, unsigned int rootParameterIndex, unsigned int descriptorOffset, const Microsoft::WRL::ComPtr<ID3D12Resource>& useResource)
{
	commandQueue.AddCommand(new SetDescriptor(descriptorOffset, rootParameterIndex, useResource));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetRootSignature(RenderCommandQueue& commandQueue, const Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature)
{
	commandQueue.AddCommand(new SetRootSignature(rootSignature));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetPipelineState(RenderCommandQueue& commandQueue, const Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState)
{
	commandQueue.AddCommand(new SetPipelineState(pipelineState));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetVertexBuffer(RenderCommandQueue& commandQueue, UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView, const Microsoft::WRL::ComPtr<ID3D12Resource>& vertexBuffer)
{
	commandQueue.AddCommand(new SetVertexBuffer(startSlot, numViews, vertexBufferView, vertexBuffer));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetIndexBuffer(RenderCommandQueue& commandQueue, D3D12_INDEX_BUFFER_VIEW* indexBufferView, const Microsoft::WRL::ComPtr<ID3D12Resource>& indexBuffer)
{
	commandQueue.AddCommand(new SetIndexBuffer(indexBufferView, indexBuffer));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetPrimitiveTopology(RenderCommandQueue& commandQueue, D3D12_PRIMITIVE_TOPOLOGY primitiveTopology)
{
	commandQueue.AddCommand(new SetPrimitiveTopology(primitiveTopology));
}