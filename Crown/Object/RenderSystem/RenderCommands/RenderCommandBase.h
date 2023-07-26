#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE
#define CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE
#include <d3d12.h>
#include <iostream>
#include "./../DirectX12Wraps/GraphicsCommandList.h"
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
			// レンタリングコマンドの基底クラスだよ☆
			// 
			//====================================================
			class RenderCommandBase
			{
			public:
				RenderCommandBase() = default;
				virtual ~RenderCommandBase() = default;

				virtual void Load(FILE* file) = 0;
				virtual void Write(FILE* file) = 0;
				virtual void Run(GraphicsCommandList& commandList) = 0;
			private:
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE