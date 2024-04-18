#pragma once
#include <string>
#include <vector>
#include <memory>

#include "DirectX12.h"
#include "Crown.h"
#include "IRenderSystem.h"
#include "GPUThread.h"
#include "SwapChain.h"
#include "CommandList.h"
#include "ResourceManager.h"


namespace Crown
{
	class RenderEngine : public IRenderSystem
	{
	public:
		RenderEngine(Window* renderTarget);
		virtual ~RenderEngine();

		virtual void Render();
	private:
		void RebuildPipeline();		//	パイプラインの再構築を行うよ☆
		void GPUThreadsSetup();		//	GPUスレッドの設定をするよ☆

		enum class CommandListName : unsigned int
		{
			DrawMainWindow,
			Copy,
			Num
		};

		enum class GPUThreadNames : unsigned int
		{
			Main,
			Num
		};

		Window* m_renderTarget;
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;

		std::vector<std::unique_ptr<GPUThread>> m_gpuThreads;
		SwapChain m_swapChain;
		std::vector<std::shared_ptr<CommandList>> m_commandLists;
		std::shared_ptr<ResourceManager> m_resourceManager;
	};
}