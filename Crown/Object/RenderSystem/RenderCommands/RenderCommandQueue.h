#pragma once
#ifndef CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDQUEUE
#define CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDQUEUE
#include <d3d12.h>
#include <vector>
#include <memory>
#include "RenderCommandBase.h"
#include <memory>
#include "./../DirectX12Wraps/GraphicsCommandList.h"
namespace Crown
{
	namespace RenderObject
	{
		namespace RenderCommand
		{
			//================================================
			// 作成日 : 2023/7/12
			// 作成者 : 服部颯澄
			// 
			// レンタリング用コマンドを保存し、実行するクラスだよ☆
			// 
			//================================================
			class RenderCommandQueue
			{
			public:
				RenderCommandQueue();
				RenderCommandQueue(ID3D12Device* device, std::vector<std::shared_ptr<RenderCommandBase>>& renderCommands,  const std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& useResource);
				~RenderCommandQueue();

				void Run(GraphicsCommandList& commandList);
			private:
				bool m_valid;
				Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_bundleCommandAllocator;
				Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_bundleCommandList;
				std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_useResource;			//	このレンタリングコマンドで使用するリソースへのポインターだよ☆
			};
		}
	}
}
#endif // !CROWN_RENDEROBJECT_RENDERCOMMAND_RENDERCOMMANDQUEUE