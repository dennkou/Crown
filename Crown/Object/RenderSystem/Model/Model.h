#pragma once
#ifndef CROWN_RENDEROBJECT_MODEL
#define CROWN_RENDEROBJECT_MODEL
#include "MaterialTag.h"
#include <DirectXMath.h>
#include "Vertices.h"
#include "MaterialMesh.h"
#include <vector>
#include <d3d12.h>
#include "./../DirectX12Wraps/DescriptorHeaps.h"
#include <string>
#include "./../DirectX12Wraps/GraphicsCommandList.h"
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// çÏê¨ì˙ : 2023/6/28
		// çÏê¨é“ : ïûïîÈDêü
		// 
		// ÉÇÉfÉãÇæÇÊÅô
		// 
		//================================================
		class Model
		{
		public:
			class ModelLoader;

			Model();
			Model(const Model& model);
			~Model();

			inline DirectX::XMFLOAT3 GetRotate() const { return m_rotate; }
			inline void SetRotate(const DirectX::XMFLOAT3& rotate) { m_rotate = rotate; }
			inline DirectX::XMFLOAT3 GetPosition() const { return m_position; }
			inline void SetPosition(const DirectX::XMFLOAT3& position) { m_position = position; }

			void LoadPMD(const std::wstring& fileName);

			void Draw(MaterialTag drawTag, GraphicsCommandList& commandList);
		private:
			DirectX::XMFLOAT3 m_position;
			DirectX::XMFLOAT3 m_rotate;

			Vertices m_vertices;
			std::vector<MaterialMesh> m_materialMeshs;
			Microsoft::WRL::ComPtr<ID3D12Resource> m_resource;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_MODEL