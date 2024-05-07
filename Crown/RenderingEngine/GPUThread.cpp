#include "GPUThread.h"
#include <assert.h>

Crown::GPUThread::GPUThread()
{
}

Crown::GPUThread::~GPUThread()
{
	CPUWait();
}

void Crown::GPUThread::Initialize(Microsoft::WRL::ComPtr<ID3D12Device> device, D3D12_COMMAND_LIST_TYPE commandListType)
{
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;					//	デッドロック対策でタイムアウトさせるよ☆
	cmdQueueDesc.NodeMask = 0;											//	マルチアダプターは考慮しないよ☆
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;		//	優先度は普通を指定するよ☆
	cmdQueueDesc.Type = commandListType;								//	コマンドリストのタイプだよ☆

	device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_commandQueue.GetAddressOf()));
	device->CreateFence(EndValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.GetAddressOf()));
}

void Crown::GPUThread::SetCommandList(CommandList* commandList, unsigned int executonPhaseIndex)
{
	CheckExecutonPhaseNum(executonPhaseIndex);
	m_executonPhase[ExecutonPhaseToIndex(executonPhaseIndex)].command.emplace_back(commandList->GetCommandList().Get());
}

void Crown::GPUThread::GPUWait(WaitInfo waitInfo, unsigned int executonPhaseIndex)
{
	CheckExecutonPhaseNum(executonPhaseIndex);
	assert(waitInfo.value);
	m_executonPhase[ExecutonPhaseToIndex(executonPhaseIndex)].wait.emplace_back(waitInfo);
}

void Crown::GPUThread::CPUWait()
{
	if(!IsEnd())
	{
		HANDLE waitEvent = CreateEvent(nullptr, false, false, nullptr);
		if (waitEvent == 0)
		{
			assert(0);
		}
		m_fence->SetEventOnCompletion(EndValue, waitEvent);
		WaitForSingleObject(waitEvent, INFINITE);
	}
}

void Crown::GPUThread::Executon()
{
	m_fence->Signal(0);
	unsigned int executonPhase = 1;								//	現在の実行フェーズだよ☆
	for (; ExecutonPhaseToIndex(executonPhase) < GetExecutonPhaseNum(); ++executonPhase)
	{
		for (const WaitInfo& waitInfo : m_executonPhase[ExecutonPhaseToIndex(executonPhase)].wait)
		{
			m_commandQueue->Wait(waitInfo.fence.Get(), waitInfo.value);
		}
		m_commandQueue->ExecuteCommandLists(static_cast<unsigned int>(m_executonPhase[ExecutonPhaseToIndex(executonPhase)].command.size()), m_executonPhase[ExecutonPhaseToIndex(executonPhase)].command.data());
		m_commandQueue->Signal(m_fence.Get(), executonPhase);
	}

	//	終了確認☆
	m_commandQueue->Signal(m_fence.Get(), EndValue);
}

void Crown::GPUThread::Reset()
{
	m_executonPhase.clear();
}

Crown::GPUThread::WaitInfo Crown::GPUThread::GetExecutonPhaseWaitInfo(unsigned int executonPhase) const noexcept
{
	WaitInfo ret;
	ret.fence = m_fence;
	ret.value = executonPhase;
    return ret;
}

void Crown::GPUThread::CheckExecutonPhaseNum(unsigned int executonPhaseIndex)
{
	assert(executonPhaseIndex);
	if (m_executonPhase.size() < executonPhaseIndex)
	{
		m_executonPhase.resize(executonPhaseIndex);
	}
}

unsigned int Crown::GPUThread::ExecutonPhaseToIndex(unsigned int executonPhaseIndex)
{
	assert(executonPhaseIndex);
	return executonPhaseIndex - 1;
}
