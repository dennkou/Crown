#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_SETPRIMITIVETOPOLOGY
#define CROWN_RENDEROBJECT_RENDERCOMMAND_SETPRIMITIVETOPOLOGY
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
			// レンタリングコマンドの基底クラスだよ☆
			// 
			//====================================================
			class SetPrimitiveTopology : public RenderCommandBase
			{
			public:
				SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY primitiveTopology);
				virtual ~SetPrimitiveTopology();

				virtual void Load(FILE* file) override;
				virtual void Write(FILE* file) override;
				virtual void Run(ID3D12GraphicsCommandList* commandList) override;
			private:
				D3D12_PRIMITIVE_TOPOLOGY m_primitiveTopology;
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_SETPRIMITIVETOPOLOGY