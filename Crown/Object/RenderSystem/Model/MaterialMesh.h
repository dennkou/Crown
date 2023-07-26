#pragma once
#ifndef CROWN_RENDEROBJECT_MATERIALPARTS
#define CROWN_RENDEROBJECT_MATERIALPARTS
#include "MaterialTag.h"
#include "Material.h"
#include "./../DirectX12Wraps/DescriptorHeaps.h"
#include <vector>
#include <memory>
#include "./../DirectX12Wraps/GraphicsCommandList.h"
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/7/4
		// 作成者 : 服部颯澄
		// 
		// マテリアルを適用する頂点情報
		// 
		//================================================
		class MaterialMesh
		{
		public:
			MaterialMesh(unsigned int indexNum, unsigned int m_indexOffset);
			~MaterialMesh();

			Material& GetMaterial(MaterialTag drawTag) { return m_materials[static_cast<int>(drawTag)]; }

			void Draw(MaterialTag drawTag, GraphicsCommandList& commandList);
		private:
			std::vector<Material> m_materials;
			unsigned int m_indexNum;
			unsigned int m_indexOffset;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_MATERIALPARTS