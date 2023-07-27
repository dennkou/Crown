#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_SETDESCRIPTORHEAP
#define CROWN_RENDEROBJECT_RENDERCOMMAND_SETDESCRIPTORHEAP
#include "RenderCommandBase.h"
namespace Crown
{
	namespace RenderObject
	{
		namespace RenderCommand
		{
			class SetDescriptorHeap : public RenderCommandBase
			{
			public:
				SetDescriptorHeap();
				virtual ~SetDescriptorHeap();

				virtual void Load(FILE* file) override;
				virtual void Write(FILE* file) override;
				virtual void Run(ID3D12GraphicsCommandList* commandList) override;
			private:

			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_SETDESCRIPTORHEAP