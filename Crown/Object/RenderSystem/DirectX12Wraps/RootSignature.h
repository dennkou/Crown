#pragma once
#ifndef CROWN_RENDEROBJECT_ROOTSIGNATURE
#define CROWN_RENDEROBJECT_ROOTSIGNATURE
#include <d3d12.h>
#include <wrl.h>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/7/5
		// 作成者 : 服部颯澄
		// 
		// ルートシグネチャーだよ☆
		// 
		//================================================
		class RootSignature
		{
		public:
			RootSignature();
			~RootSignature();

			void Create(ID3D12Device* device);

			Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature() const noexcept { return m_rootSignature; };
		private:
			Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_ROOTSIGNATURE