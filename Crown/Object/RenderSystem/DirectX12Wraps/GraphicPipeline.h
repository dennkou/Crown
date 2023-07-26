#pragma once
#ifndef CROWN_RENDEROBJECT_GRAPHICSPIPELINE
#define CROWN_RENDEROBJECT_GRAPHICSPIPELINE
#include <d3d12.h>
#include <wrl.h>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/4/26
		// 作成者 : 服部颯澄
		// 
		// DirectX12でグラフィックパイプラインの管理を行うクラスだよ☆
		// 
		//================================================
		class GraphicsPipeline
		{
		public:
			GraphicsPipeline();
			~GraphicsPipeline();

			void ChangeGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& newStateDisc);
			inline Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState() const { return m_pipelineState; }
			inline D3D12_GRAPHICS_PIPELINE_STATE_DESC GetState() const { return m_nawState; }

			inline void SetRootSignature(ID3D12RootSignature* rootSignature) { m_nawState.pRootSignature = rootSignature; }
			inline void SetVS(LPVOID pointer, SIZE_T bufferSize) { m_nawState.VS.pShaderBytecode = pointer; m_nawState.VS.BytecodeLength = bufferSize; }
			inline void SetVS(ID3DBlob& vs) { m_nawState.VS.pShaderBytecode = vs.GetBufferPointer(); m_nawState.VS.BytecodeLength = vs.GetBufferSize(); }
			inline void SetPS(LPVOID pointer, SIZE_T bufferSize) { m_nawState.PS.pShaderBytecode = pointer; m_nawState.PS.BytecodeLength = bufferSize; }
			inline void SetPS(ID3DBlob& ps) { m_nawState.PS.pShaderBytecode = ps.GetBufferPointer(); m_nawState.PS.BytecodeLength = ps.GetBufferSize(); }
			inline void SetHS(LPVOID pointer, SIZE_T bufferSize) { m_nawState.HS.pShaderBytecode = pointer; m_nawState.HS.BytecodeLength = bufferSize; }
			inline void SetHS(ID3DBlob& hs) { m_nawState.HS.pShaderBytecode = hs.GetBufferPointer(); m_nawState.HS.BytecodeLength = hs.GetBufferSize(); }
			inline void SetDS(LPVOID pointer, SIZE_T bufferSize) { m_nawState.DS.pShaderBytecode = pointer; m_nawState.DS.BytecodeLength = bufferSize; }
			inline void SetDS(ID3DBlob& ds) { m_nawState.DS.pShaderBytecode = ds.GetBufferPointer(); m_nawState.DS.BytecodeLength = ds.GetBufferSize(); }
			inline void SetGS(LPVOID pointer, SIZE_T bufferSize) { m_nawState.GS.pShaderBytecode = pointer; m_nawState.GS.BytecodeLength = bufferSize; }
			inline void SetGS(ID3DBlob& gs) { m_nawState.GS.pShaderBytecode = gs.GetBufferPointer(); m_nawState.GS.BytecodeLength = gs.GetBufferSize(); }
			inline void SetStreamOutput(D3D12_STREAM_OUTPUT_DESC& streamOutput) { m_nawState.StreamOutput = streamOutput; }
			inline void SetBlendState(D3D12_BLEND_DESC& blendState) { m_nawState.BlendState = blendState; }
			inline void SetSampleMask(UINT sampleMask) { m_nawState.SampleMask = sampleMask; }
			inline void SetRasterizerState(D3D12_RASTERIZER_DESC& rasterizerState) { m_nawState.RasterizerState = rasterizerState; }
			inline void SetDepthStencilState(D3D12_DEPTH_STENCIL_DESC& depthStencilState) { m_nawState.DepthStencilState = depthStencilState; }
			inline void SetInputLayout(const D3D12_INPUT_LAYOUT_DESC& inputLayout) { m_nawState.InputLayout = inputLayout; }
			inline void SetIBStripCutValue(D3D12_INDEX_BUFFER_STRIP_CUT_VALUE& iBStripCutValue) { m_nawState.IBStripCutValue = iBStripCutValue; }
			inline void SetPrimitiveTopologyType(D3D12_PRIMITIVE_TOPOLOGY_TYPE& PrimitiveTopologyType) { m_nawState.PrimitiveTopologyType = PrimitiveTopologyType; }
			inline void SetNumRenderTargets(UINT numRenderTargets) { m_nawState.NumRenderTargets = numRenderTargets; }
			inline void SetRTVFormats(int index, DXGI_FORMAT rtvFormate) { m_nawState.RTVFormats[index] = rtvFormate; }
			inline void SetDSVFormat(DXGI_FORMAT dsvFormat) { m_nawState.DSVFormat = dsvFormat; }
			inline void SetSampleDesc(DXGI_SAMPLE_DESC& sampleDesc) { m_nawState.SampleDesc = sampleDesc; }
			inline void SetNodeMask(UINT nodeMask) { m_nawState.NodeMask = nodeMask; }
			inline void SetCachedPSO(D3D12_CACHED_PIPELINE_STATE cachedPSO) { m_nawState.CachedPSO = cachedPSO; }
			inline void SetFlags(D3D12_PIPELINE_STATE_FLAGS flags) { m_nawState.Flags = flags; }

			void Commit(ID3D12Device& device);
		private:
			D3D12_GRAPHICS_PIPELINE_STATE_DESC m_nawState;
			Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_GRAPHICSPIPELINE