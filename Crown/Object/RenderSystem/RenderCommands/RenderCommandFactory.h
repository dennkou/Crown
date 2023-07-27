#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDLIST
#define CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDLIST
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include "RenderCommandBase.h"

namespace Crown
{
	namespace RenderObject
	{
		namespace RenderCommand
		{
			//====================================================
			// 作成日 : 2023/7/12
			// 作成者 : 服部颯澄
			// 
			// レンタリングコマンドの作成、保存をするクラスだよ☆
			// 
			//====================================================
			class RenderCommandFactory
			{
			public:
				RenderCommandFactory();
				~RenderCommandFactory();

				static void CreateSetDescriptorHeap(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue);
				static void CreateSetDescriptor(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, unsigned int rootParameterIndex, unsigned int descriptorOffset);
				static void CreateSetRootSignature(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, const Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature);
				static void CreateSetPipelineState(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, const Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState);
				static void CreateSetVertexBuffer(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView);
				static void CreateSetIndexBuffer(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, D3D12_INDEX_BUFFER_VIEW* indexBufferView);
				static void CreateSetPrimitiveTopology(std::vector<std::shared_ptr<RenderCommandBase>>& commandQueue, D3D12_PRIMITIVE_TOPOLOGY primitiveTopology);
			private:
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDLIST