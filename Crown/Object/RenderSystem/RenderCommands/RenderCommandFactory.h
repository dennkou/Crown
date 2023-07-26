#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDLIST
#define CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDLIST
#include <d3d12.h>
#include <iostream>
#include "RenderCommandQueue.h"
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

				static void Load(FILE* file, RenderCommandQueue& commandQueue);
				static void Write(FILE* file, RenderCommandQueue* commandQueue);

				static void CreateSetDescriptorHeap(RenderCommandQueue& commandQueue);
				static void CreateSetDescriptor(RenderCommandQueue& commandQueue, unsigned int rootParameterIndex, unsigned int descriptorOffset, const Microsoft::WRL::ComPtr<ID3D12Resource>& useResource);
				static void CreateSetRootSignature(RenderCommandQueue& commandQueue, const Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature);
				static void CreateSetPipelineState(RenderCommandQueue& commandQueue, const Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState);
				static void CreateSetVertexBuffer(RenderCommandQueue& commandQueue, UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView, const Microsoft::WRL::ComPtr<ID3D12Resource>& vertexBuffer);
				static void CreateSetIndexBuffer(RenderCommandQueue& commandQueue, D3D12_INDEX_BUFFER_VIEW* indexBufferView, const Microsoft::WRL::ComPtr<ID3D12Resource>& indexBuffer);
				static void CreateSetPrimitiveTopology(RenderCommandQueue& commandQueue, D3D12_PRIMITIVE_TOPOLOGY primitiveTopology);
			private:
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDLIST