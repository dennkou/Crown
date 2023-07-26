#pragma once
#ifndef CROWN_RENDEROBJECT_VERTICES
#define CROWN_RENDEROBJECT_VERTICES
#include <d3d12.h>
#include <DirectXMath.h>
#include <vector>
#include <wrl.h>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/28
		// 作成者 : 服部颯澄
		// 
		// 頂点データを扱うクラスだよ☆
		// 
		//================================================
		class Vertices
		{
		public:
			//	頂点データの定義だよ☆
			struct VerticesData
			{
				DirectX::XMFLOAT3 pos;
				DirectX::XMFLOAT3 normal;
				DirectX::XMFLOAT2 uv;
				unsigned int boneIndex[2];
				float boneWeight;

				VerticesData() = default;
				VerticesData(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 normal, DirectX::XMFLOAT2 uv, unsigned int boneIndex[2], float boneWeight)
					:
					pos(pos),
					normal(normal),
					uv(uv),
					boneWeight(boneWeight)
				{
					this->boneIndex[0] = boneIndex[0];
					this->boneIndex[1] = boneIndex[1];
				}
			};
			Vertices();
			~Vertices();

			void CreateBuffer(ID3D12Device* device, std::vector<VerticesData>& vertices, std::vector<unsigned int>& indexBuffer);

			inline D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView()						{ return &m_vertexBufferView; }
			inline const Microsoft::WRL::ComPtr<ID3D12Resource> GetConstVertexBuffer()	{ return m_vertexBuffer; }
			inline D3D12_INDEX_BUFFER_VIEW* GetIndexBufferView()						{ return &m_indexBufferView; }
			inline const Microsoft::WRL::ComPtr<ID3D12Resource> GetConstIndexBuffer()	{ return m_indexBuffer; }
			D3D12_INPUT_LAYOUT_DESC GetInputLayoutDesc();

		private:
			Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer;
			D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

			Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBuffer;
			D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

			static const D3D12_INPUT_ELEMENT_DESC m_inputLayout[5];
		};
	}
}
#endif // !CROWN_RENDEROBJECT_VERTICES