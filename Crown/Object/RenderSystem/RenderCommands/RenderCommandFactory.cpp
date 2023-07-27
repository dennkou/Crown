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

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetDescriptorHeap(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue)
{
	commandQueue.emplace_back(std::make_shared<SetDescriptorHeap>());
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetDescriptor(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, unsigned int rootParameterIndex, unsigned int descriptorOffset)
{
	commandQueue.emplace_back(std::make_shared<SetDescriptor>(descriptorOffset, rootParameterIndex));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetRootSignature(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, const Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature)
{
	commandQueue.emplace_back(std::make_shared<SetRootSignature>(rootSignature));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetPipelineState(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, const Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState)
{
	commandQueue.emplace_back(std::make_shared<SetPipelineState>(pipelineState));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetVertexBuffer(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView)
{
	commandQueue.emplace_back(std::make_shared<SetVertexBuffer>(startSlot, numViews, vertexBufferView));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetIndexBuffer(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, D3D12_INDEX_BUFFER_VIEW* indexBufferView)
{
	commandQueue.emplace_back(std::make_shared<SetIndexBuffer>(indexBufferView));
}

void Crown::RenderObject::RenderCommand::RenderCommandFactory::CreateSetPrimitiveTopology(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, D3D12_PRIMITIVE_TOPOLOGY primitiveTopology)
{
	commandQueue.emplace_back(std::make_shared<SetPrimitiveTopology>(primitiveTopology));
}