#pragma once
#include <vector>
#include "DirectX12.h"
#include "CommandList.h"

namespace Crown
{
	//	GPU側のスレッドだよ☆
	class GPUThread
	{
	public:
		GPUThread(Microsoft::WRL::ComPtr<ID3D12Device> device);
		~GPUThread();

		/// <summary>
		/// 実行するコマンドリスト設定するよ☆
		/// </summary>
		/// <param name="commandList"> 実行するコマンドリスト☆ </param>
		/// <param name="ExecutonPhaseIndex"> 実行順☆ </param>
		void SetCommandList(CommandList* commandList, unsigned int executonPhaseIndex);

		/// <summary>
		/// 他のGPUThreadが特定のコマンドリストを実行し終わるまで待機するよ☆
		/// </summary>
		/// <param name="thread"> 待つ対象☆ </param>
		/// <param name="Value"> 何個目が終るまで待機するか☆ </param>
		/// <param name="ExecutonPhaseIndex"> 待機するフェーズ☆ </param>
		void GPUWait(GPUThread* thread, unsigned int value, unsigned int executonPhaseIndex);

		//	実行が終るまでCPUを待機させるよ☆
		void CPUWait();

		/// <summary>
		/// コマンドを実行するよ☆
		/// </summary>
		void Executon();

		void Reset();

		inline unsigned int GetExecutonPhaseNum() const noexcept { return static_cast<unsigned int>(m_executonPhase.size()); }
		inline Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetCommandQueue() const noexcept { return m_commandQueue; }
	private:
		void CheckExecutonPhaseNum(unsigned int executonPhaseIndex);			//	実行フェーズ配列を確認するよ☆
		unsigned int ExecutonPhaseToIndex(unsigned int executonPhaseIndex);		//	実行フェーズをインデックスに変換するよ☆

		struct WaitInfo
		{
			Microsoft::WRL::ComPtr<ID3D12Fence> fence;
			unsigned int value;
		};
		//	各フェーズで実行するべきことだよ☆
		struct ExecutonPhase
		{
			std::vector<WaitInfo> wait;
			std::vector<ID3D12CommandList*> command;
		};
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
		std::vector<ExecutonPhase> m_executonPhase;

	};
}