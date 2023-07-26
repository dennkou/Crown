#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_SETINDEXBUFFER
#define CROWN_RENDEROBJECT_RENDERCOMMAND_SETINDEXBUFFER
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
			class SetIndexBuffer : public RenderCommandBase
			{
			public:
				SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView, Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer);
				virtual ~SetIndexBuffer();

				virtual void Load(FILE* file) override;
				virtual void Write(FILE* file) override;
				virtual void Run(GraphicsCommandList& commandList) override;
			private:
				D3D12_INDEX_BUFFER_VIEW* m_indexBufferView;
				Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBuffer;
			};
		}
	}
}
#endif //!CROWN_RENDEROBJECT_RENDERCOMMAND_SETINDEXBUFFER