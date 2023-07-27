#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE
#define CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE
#include <d3d12.h>
#include <iostream>
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
				virtual void Run(ID3D12GraphicsCommandList* commandList) = 0;
			private:
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE