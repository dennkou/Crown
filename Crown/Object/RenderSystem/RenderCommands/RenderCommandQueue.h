#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDQUEUE
#define CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDQUEUE
#include <d3d12.h>
#include <vector>
#include <memory>
#include "RenderCommandBase.h"
#include <memory>
#include "./../DirectX12Wraps/GraphicsCommandList.h"
namespace Crown
{
	namespace RenderObject
	{
		namespace RenderCommand
		{
			//================================================
			// 作成日 : 2023/7/12
			// 作成者 : 服部颯澄
			// 
			// レンタリング用コマンドを保存し、実行するクラスだよ☆
			// 
			//================================================
			class RenderCommandQueue
			{
			public:
				RenderCommandQueue();
				~RenderCommandQueue();

				void AddCommand(RenderCommandBase* command);
				void Run(GraphicsCommandList& commandList);
			private:
				bool loakFlag = false;
				std::vector<std::shared_ptr<RenderCommandBase>> m_renderCommands;
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDQUEUE