#pragma once
#ifndef CROWN_RENDEROBJECT_PMX
#define CROWN_RENDEROBJECT_PMX
#include <d3d12.h>
#include <string>
#include <vector>
#include "./../../TextureBuffer.h"
#include "./../Vertices.h"
#include "./../MaterialMesh.h"
#include "./../../DirectX12Wraps/RootSignature.h"
#include "./../../DirectX12Wraps/GraphicPipeline.h"
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/7/31
		// 作成者 : 服部颯澄
		// 
		// Pmd形式のモデルデータを作成するクラスだよ☆
		//
		//================================================
		class Pmd
		{
		public:
			static void Load(ID3D12Device* device, std::wstring& fileName, TextureBuffer& textureBuffer, Vertices& verticesBuffer, std::vector<MaterialMesh>& materialMeshs, unsigned int descriptorOffset, Microsoft::WRL::ComPtr<ID3D12Resource> resource);
		private:
			static RootSignature* rootSignature;
			static GraphicsPipeline* graphicsPipeline;
			static const D3D12_INPUT_ELEMENT_DESC inputLayout[5];
		};
	}
}
#endif // !CROWN_RENDEROBJECT_PMX