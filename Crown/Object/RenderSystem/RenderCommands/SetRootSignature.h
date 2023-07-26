#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_SETROOTSIGNATURE
#define CROWN_RENDEROBJECT_RENDERCOMMAND_SETROOTSIGNATURE
#include "RenderCommandBase.h"
namespace Crown
{
	namespace RenderObject
	{
		namespace RenderCommand
		{
			class SetRootSignature : public RenderCommandBase
			{
			public:
				SetRootSignature(Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature);
				virtual ~SetRootSignature();

				virtual void Load(FILE* file) override;
				virtual void Write(FILE* file) override;
				virtual void Run(GraphicsCommandList& commandList) override;
			private:
				Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
			};
		}
	}
}
#endif //!CROWN_RENDEROBJECT_RENDERCOMMAND_SETROOTSIGNATURE