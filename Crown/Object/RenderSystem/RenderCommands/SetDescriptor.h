#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_SETDESCRIPTOR
#define CROWN_RENDEROBJECT_RENDERCOMMAND_SETDESCRIPTOR
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
			// ディスクリプタをセットする
			// 
			//====================================================
			class SetDescriptor : public RenderCommandBase
			{
			public:
				SetDescriptor(unsigned int descriptorOffset, unsigned int rootParameterIndex);
				virtual ~SetDescriptor();

				void Load(FILE* file) override;
				void Write(FILE* file) override;
				void Run(ID3D12GraphicsCommandList* commandList) override;
			private:
				unsigned int m_offset;
				unsigned int m_rootParameterIndex;
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDBASE