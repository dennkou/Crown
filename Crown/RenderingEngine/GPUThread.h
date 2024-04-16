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
		GPUThread(Microsoft::WRL::ComPtr<ID3D12Device> device);
		~GPUThread();

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
		void GPUWait(GPUThread* thread, unsigned int value, unsigned int executonPhaseIndex);

		//	���s���I��܂�CPU��ҋ@������恙
		void CPUWait();

		/// <summary>
		/// �R�}���h�����s����恙
		/// </summary>
		void Executon();

		void Reset();

		inline unsigned int GetExecutonPhaseNum() const noexcept { return static_cast<unsigned int>(m_executonPhase.size()); }
		inline Microsoft::WRL::ComPtr<ID3D12CommandQueue> GetCommandQueue() const noexcept { return m_commandQueue; }
	private:
		void CheckExecutonPhaseNum(unsigned int executonPhaseIndex);			//	���s�t�F�[�Y�z����m�F����恙
		unsigned int ExecutonPhaseToIndex(unsigned int executonPhaseIndex);		//	���s�t�F�[�Y���C���f�b�N�X�ɕϊ�����恙

		struct WaitInfo
		{
			Microsoft::WRL::ComPtr<ID3D12Fence> fence;
			unsigned int value;
		};
		//	�e�t�F�[�Y�Ŏ��s����ׂ����Ƃ��恙
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