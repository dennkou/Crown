#include "GraphicPipeline.h"
#include "d3dx12.h"

Crown::RenderObject::GraphicsPipeline::GraphicsPipeline()
{
	m_pipelineState = nullptr;
	
	//	デフォルトの状態を定義するよ☆
	m_nawState.pRootSignature = nullptr;
	m_nawState.VS.pShaderBytecode = nullptr;
	m_nawState.VS.BytecodeLength = 0;
	m_nawState.PS.pShaderBytecode = nullptr;
	m_nawState.PS.BytecodeLength = 0;
	m_nawState.HS.pShaderBytecode = nullptr;
	m_nawState.HS.BytecodeLength = 0;
	m_nawState.DS.pShaderBytecode = nullptr;
	m_nawState.DS.BytecodeLength = 0;
	m_nawState.GS.pShaderBytecode = nullptr;
	m_nawState.GS.BytecodeLength = 0;
	m_nawState.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	m_nawState.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	m_nawState.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	m_nawState.NumRenderTargets = 1;
	m_nawState.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_nawState.DepthStencilState.DepthEnable = true;
	m_nawState.DepthStencilState.StencilEnable = false;
	m_nawState.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	m_nawState.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	m_nawState.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	m_nawState.BlendState.AlphaToCoverageEnable = false;
	m_nawState.BlendState.IndependentBlendEnable = false;
	m_nawState.BlendState.RenderTarget->BlendEnable = true;
	m_nawState.BlendState.RenderTarget->SrcBlend = D3D12_BLEND_SRC_ALPHA;
	m_nawState.BlendState.RenderTarget->DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	m_nawState.BlendState.RenderTarget->BlendOp = D3D12_BLEND_OP_ADD;
	m_nawState.NodeMask = 0;
	m_nawState.SampleDesc.Count = 1;
	m_nawState.SampleDesc.Quality = 0;
	m_nawState.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	m_nawState.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc = {};
	renderTargetBlendDesc.BlendEnable = false;
	renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	renderTargetBlendDesc.LogicOpEnable = false;

	m_nawState.BlendState.RenderTarget[0] = renderTargetBlendDesc;
}

Crown::RenderObject::GraphicsPipeline::~GraphicsPipeline()
{
}

void Crown::RenderObject::GraphicsPipeline::ChangeGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& newStateDisc)
{
	m_nawState = newStateDisc;
}

void Crown::RenderObject::GraphicsPipeline::Commit(ID3D12Device& device)
{
	if (m_pipelineState != nullptr)
	{
		m_pipelineState.Reset();
	}
	device.CreateGraphicsPipelineState(&m_nawState, IID_PPV_ARGS(&m_pipelineState));
}