#include "SetPipelineState.h"

Crown::RenderObject::RenderCommand::SetPipelineState::SetPipelineState(const Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState)
	:
	m_pipelineState(pipelineState)
{
}

Crown::RenderObject::RenderCommand::SetPipelineState::~SetPipelineState()
{
}

void Crown::RenderObject::RenderCommand::SetPipelineState::Load(FILE* file)
{

}

void Crown::RenderObject::RenderCommand::SetPipelineState::Write(FILE* file)
{

}

void Crown::RenderObject::RenderCommand::SetPipelineState::Run(GraphicsCommandList& commandList)
{
	commandList.GetGraphicsCommandList()->SetPipelineState(m_pipelineState.Get());
}