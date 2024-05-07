#pragma once
#include "DirectX12.h"

namespace Crown
{
	class TextureManager
	{
	public:
		struct RGBA
		{
			unsigned char r, g, b, a;
		};

		TextureManager();
		~TextureManager();


		//void Initialize(Microsoft::WRL::ComPtr<ID3D12Device> device, ID3D12GraphicsCommandList* copyCommandList, DescriptorHeaps* descriptorHeap);
		
	private:

	};
}