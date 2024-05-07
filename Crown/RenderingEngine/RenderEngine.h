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
		static constexpr int BackBufferNum = 2;

		void RebuildPipeline();		//	�p�C�v���C���̍č\�z���s���恙
		void GPUThreadsSetup();		//	GPU�X���b�h�̐ݒ������恙

		enum class CommandListNames : unsigned int
		{
			DrawMainWindow,
			Num
		};

		enum class GPUThreadNames : unsigned int
		{
			Main,
			Num
		};

		Window* m_renderTarget;
		Microsoft::WRL::ComPtr<ID3D12Device> m_device;

		GPUThread m_gpuThread;

		SwapChain m_swapChain;
		std::vector<std::shared_ptr<CommandList>> m_commandLists;
		std::shared_ptr<ResourceManager> m_resourceManager;
	};
}