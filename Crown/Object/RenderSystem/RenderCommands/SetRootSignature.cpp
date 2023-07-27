#include "SetRootSignature.h"

Crown::RenderObject::RenderCommand::SetRootSignature::SetRootSignature(Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature)
	:
	m_rootSignature(rootSignature)
{

}

Crown::RenderObject::RenderCommand::SetRootSignature::~SetRootSignature()
{

}

void Crown::RenderObject::RenderCommand::SetRootSignature::Load(FILE* file)
{

}

void Crown::RenderObject::RenderCommand::SetRootSignature::Write(FILE* file)
{

}

void Crown::RenderObject::RenderCommand::SetRootSignature::Run(ID3D12GraphicsCommandList* commandList)
{
	commandList->SetGraphicsRootSignature(m_rootSignature.Get());
}
