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
		struct WaitInfo
		{
			Microsoft::WRL::ComPtr<ID3D12Fence> fence;
			unsigned int value = 0;
		};

		GPUThread();
		~GPUThread();

		void Initialize(Microsoft::WRL::ComPtr<ID3D12Device> device, D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT);

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
		void GPUWait(WaitInfo waitInfo, unsigned int executonPhaseIndex);

		//	実行が終るまでCPUを待機させるよ☆
		void CPUWait();

		inline bool IsEnd() const noexcept { return m_fence->GetCompletedValue() == EndValue; }

		/// <summary>
		/// コマンドを実行するよ☆
		/// </summary>
		void Executon();

		void Reset();

		inline constexpr unsigned int GetExecutonPhaseNum() const noexcept { return static_cast<unsigned int>(m_executonPhase.size()); }

		WaitInfo GetExecutonPhaseWaitInfo(unsigned int executonPhase) const noexcept;
		inline Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetCommandQueue() noexcept { return m_commandQueue; }
	private:
		void CheckExecutonPhaseNum(unsigned int executonPhaseIndex);			//	実行フェーズ配列を確認するよ☆
		unsigned int ExecutonPhaseToIndex(unsigned int executonPhaseIndex);		//	実行フェーズ番号を実行フェーズインデックスに変換するよ☆

		static constexpr UINT64 EndValue = UINT64_MAX - 1;

		//	各フェーズで実行するべきことだよ☆
		struct ExecutonPhase
		{
			std::vector<WaitInfo> wait;
			std::vector<ID3D12CommandList*> command;
		};

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;				//	管理しているCommandQueueとの同期用のフェンスだよ☆	このフェンスの値はCommandQueueの実行フェーズと一致し
		std::vector<ExecutonPhase> m_executonPhase;

	};
}