#pragma once
#ifndef CROWN_RENDEROBJECT_MATERIAL
#define CROWN_RENDEROBJECT_MATERIAL
#include "./../DirectX12Wraps/GraphicPipeline.h"
#include "./../RenderCommands/RenderCommandQueue.h"
#include "./../DirectX12Wraps/DescriptorHeaps.h"
#include <memory>
#include <vector>
#include <d3d12.h>
#include <wrl.h>
#include "./../BlobConstBuffer/BlobConstBuffer.h"
#include "./../DirectX12Wraps/GraphicsCommandList.h"
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/7/4
		// 作成者 : 服部颯澄
		// 
		// マテリアル情報を格納するよ☆
		// 
		//================================================
		class Material
		{
		public:
			Material();
			~Material();

			void CreateData(RenderCommand::RenderCommandQueue& commandQueue, std::vector<BlobConstBuffer>& constantBuffers);

			void Draw(GraphicsCommandList& commandList);
			BlobConstBuffer& GetConstBuffer(unsigned int constantBufferIndex);
		private:
			std::vector<BlobConstBuffer> m_constBuffers;							//	使用するコンスタントバッファだよ☆
			RenderCommand::RenderCommandQueue m_commandQueue;						//	ドローで使用するコマンドだよ☆
		};
	}
}
#endif // !CROWN_RENDEROBJECT_MATERIAL