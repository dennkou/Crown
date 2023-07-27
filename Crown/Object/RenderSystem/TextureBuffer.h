#pragma once
#ifndef CROWN_RENDEROBJECT_TEXTUREBUFFER
#define CROWN_RENDEROBJECT_TEXTUREBUFFER
#include "DirectX12Wraps/DescriptorHeaps.h"
#include <unordered_map>
#include <string>
#include <d3d12.h>
#include <wrl.h>
#include <functional>
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/7/6
		// 作成者 : 服部颯澄
		// 
		// テクスチャの管理を行うよ☆
		// 
		//================================================
		class TextureBuffer
		{
		public:
			struct RGBA
			{
				unsigned char r, g, b, a;
			};

			TextureBuffer();
			~TextureBuffer();


			void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* copyCommandList, DescriptorHeaps* descriptorHeap);

			/// <summary>
			/// テクスチャのディスクリプタヒープオフセットを取得するよ☆
			/// </summary>
			/// <param name="filePath"></param>
			/// <returns></returns>
			unsigned int TextureAcquisition(std::wstring filePath);

			/// <summary>
			/// テクスチャのバッファを取得するよ☆
			/// </summary>
			/// <returns></returns>
			const Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureBuffer(unsigned int offset);

			/// <summary>
			/// 渡されたRGBA配列をテクスチャとして登録するよ☆
			/// </summary>
			/// <param name="dataName"></param>
			/// <param name="width"></param>
			/// <param name="height"></param>
			/// <param name="data"></param>
			void CreateTextureData(std::wstring dataName, UINT width, UINT height, RGBA* data);

		private:
			void CreateData(std::wstring dataName, UINT width, UINT height, UINT rowPitch, DXGI_FORMAT format, uint8_t* pixels);

			ID3D12Device* m_device;
			DescriptorHeaps* m_descriptorHeap;
			ID3D12GraphicsCommandList* m_copyCommandList;
			std::unordered_map<std::wstring, unsigned int> m_textureDescriptorHeapOffsets;
			std::unordered_map<unsigned int, Microsoft::WRL::ComPtr<ID3D12Resource>> m_resources;
			std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_uploadBuffer;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_TEXTUREBUFFER