#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_SETVERTEXBUFFER
#define CROWN_RENDEROBJECT_RENDERCOMMAND_SETVERTEXBUFFER
#include "./RenderCommandBase.h"
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
			class SetVertexBuffer	:	public RenderCommandBase
			{
			public:
				SetVertexBuffer(UINT startSlot, UINT numViews, D3D12_VERTEX_BUFFER_VIEW* vertexBufferView);
				virtual ~SetVertexBuffer();

				virtual void Load(FILE* file) override;
				virtual void Write(FILE* file) override;
				virtual void Run(ID3D12GraphicsCommandList* commandList) override;
			private:
				UINT m_startSlot;
				UINT m_numViews;
				D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
			};
		}
	}
}
#endif //!CROWN_RENDEROBJECT_RENDERCOMMAND_SETVERTEXBUFFER