#pragma once
#ifndef CROWN_RENDERSYSTEM
#define CROWN_RENDERSYSTEM
#include <d3d12.h>
#include "DirectX12Wraps/GraphicsCommandList.h"
#include "DirectX12Wraps/SwapChain.h"
#include "Model/ModelManager.h"
#include "DirectX12Wraps/RootSignature.h"
#include <wrl.h>

#include "TextureBuffer.h"

namespace Crown
{
	namespace RenderObject
	{
	//================================================================================
	// 作成日 : 2023/6/27
	// 作成者 : 服部颯澄
	// 
	// 描画全体の統括を行うクラスだよ☆
	// 
	//================================================================================
		class RenderSystem
		{
		public:
			RenderSystem(Crown::Window& renderTargetWindow);
			~RenderSystem();

			/// <summary>
			/// 描画エンジン全体の初期化をするよ☆
			/// </summary>
			void Initialize();

			/// <summary>
			/// 表示内容の更新をするよ☆
			/// </summary>
			void Update();

			ModelManager& GetModelManager() { return m_modelManager; }
			ID3D12Device* GetDevice() { return m_device.Get(); }
		private:
			Crown::Window& m_renderTargetWindow;			//	描画対象のウィンドウだよ☆

			Microsoft::WRL::ComPtr<ID3D12Device> m_device;

			GraphicsCommandList m_commandList;
			SwapChain m_swapChain;

			ModelManager m_modelManager;
			TextureBuffer m_textureBuffer;
		};
	}
}
#endif // !CROWN_RENDERSYSTEM