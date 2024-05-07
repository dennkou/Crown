#pragma once
#include <vector>
#include "DirectX12.h"
#include "CommandList.h"

namespace Crown
{
	//	GPU���̃X���b�h���恙
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
		/// ���s����R�}���h���X�g�ݒ肷��恙
		/// </summary>
		/// <param name="commandList"> ���s����R�}���h���X�g�� </param>
		/// <param name="ExecutonPhaseIndex"> ���s���� </param>
		void SetCommandList(CommandList* commandList, unsigned int executonPhaseIndex);

		/// <summary>
		/// ����GPUThread������̃R�}���h���X�g�����s���I���܂őҋ@����恙
		/// </summary>
		/// <param name="thread"> �҂Ώہ� </param>
		/// <param name="Value"> ���ڂ��I��܂őҋ@���邩�� </param>
		/// <param name="ExecutonPhaseIndex"> �ҋ@����t�F�[�Y�� </param>
		void GPUWait(WaitInfo waitInfo, unsigned int executonPhaseIndex);

		//	���s���I��܂�CPU��ҋ@������恙
		void CPUWait();

		inline bool IsEnd() const noexcept { return m_fence->GetCompletedValue() == EndValue; }

		/// <summary>
		/// �R�}���h�����s����恙
		/// </summary>
		void Executon();

		void Reset();

		inline constexpr unsigned int GetExecutonPhaseNum() const noexcept { return static_cast<unsigned int>(m_executonPhase.size()); }

		WaitInfo GetExecutonPhaseWaitInfo(unsigned int executonPhase) const noexcept;
		inline Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetCommandQueue() noexcept { return m_commandQueue; }
	private:
		void CheckExecutonPhaseNum(unsigned int executonPhaseIndex);			//	���s�t�F�[�Y�z����m�F����恙
		unsigned int ExecutonPhaseToIndex(unsigned int executonPhaseIndex);		//	���s�t�F�[�Y�ԍ������s�t�F�[�Y�C���f�b�N�X�ɕϊ�����恙

		static constexpr UINT64 EndValue = UINT64_MAX - 1;

		//	�e�t�F�[�Y�Ŏ��s����ׂ����Ƃ��恙
		struct ExecutonPhase
		{
			std::vector<WaitInfo> wait;
			std::vector<ID3D12CommandList*> command;
		};

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;				//	�Ǘ����Ă���CommandQueue�Ƃ̓����p�̃t�F���X���恙	���̃t�F���X�̒l��CommandQueue�̎��s�t�F�[�Y�ƈ�v��
		std::vector<ExecutonPhase> m_executonPhase;

	};
}