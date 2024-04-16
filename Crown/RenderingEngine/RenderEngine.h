#pragma once
#include <string>
#include <vector>

#include "DirectX12.h"
#include "Crown.h"
#include "IRenderSystem.h"
#include "GPUThread.h"
#include "SwapChain.h"
#include "CommandList.h"

namespace Crown
{
	class RenderEngine : public IRenderSystem
	{
	public:
		RenderEngine(Window* renderTarget);
		virtual ~RenderEngine();

		virtual void Render();
	private:
		void RebuildPipeline();
		void GPUThreadsSetup();

		enum class CommandListName : unsigned int
		{
			DrawMainWindow,
			CopyOnly,
			Num
		};

		enum class GPUThreadNames : unsigned int
		{
			Main,
			Num
		};

		Window* m_renderTarget;
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;

		std::vector<GPUThread*> m_gpuThreads;
		SwapChain m_swapChain;
		std::vector<CommandList*> m_commandLists;
	};
}