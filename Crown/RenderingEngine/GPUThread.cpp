#include "GPUThread.h"
#include <assert.h>

Crown::GPUThread::GPUThread(Microsoft::WRL::ComPtr<ID3D12Device> device)
{

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;				//	デッドロック対策でタイムアウトさせるよ☆
	cmdQueueDesc.NodeMask = 0;										//	マルチアダプターは考慮しないよ☆
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	//	優先度は普通を指定するよ☆
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;				//	コマンドリストのタイプはダイレクトコマンドリストだよ☆

	device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_commandQueue.GetAddressOf()));
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_fence.GetAddressOf()));
}

Crown::GPUThread::~GPUThread()
{
	CPUWait();
}

void Crown::GPUThread::SetCommandList(CommandList* commandList, unsigned int executonPhaseIndex)
{
	CheckExecutonPhaseNum(executonPhaseIndex);
	m_executonPhase[ExecutonPhaseToIndex(executonPhaseIndex)].command.emplace_back(commandList->GetCommandList().Get());
}

void Crown::GPUThread::GPUWait(const GPUThread* const thread, unsigned int value, unsigned int executonPhaseIndex)
{
	CheckExecutonPhaseNum(executonPhaseIndex);
	assert(value);
	m_executonPhase[ExecutonPhaseToIndex(executonPhaseIndex)].wait.emplace_back();
	m_executonPhase[ExecutonPhaseToIndex(executonPhaseIndex)].wait.back().value = value;
	m_executonPhase[ExecutonPhaseToIndex(executonPhaseIndex)].wait.back().fence = thread->m_fence;
}

void Crown::GPUThread::CPUWait()
{
	m_commandQueue->Signal(m_fence.Get(), GetExecutonPhaseNum() + 1);
	HANDLE waitEvent = CreateEvent(nullptr, false, false, nullptr);
	if (waitEvent == 0)
	{
		assert(0);
	}
	m_fence->SetEventOnCompletion(GetExecutonPhaseNum() + 1, waitEvent);
	WaitForSingleObject(waitEvent, INFINITE);
	m_fence->Signal(0);
}

void Crown::GPUThread::Executon()
{
	unsigned int executonPhase = 1;								//	現在の実行フェーズだよ☆
	const unsigned int executonPhaseNum = static_cast<unsigned int>(m_executonPhase.size());
	for (; ExecutonPhaseToIndex(executonPhase) < executonPhaseNum; ++executonPhase)
	{
		for (const WaitInfo& waitInfo : m_executonPhase[ExecutonPhaseToIndex(executonPhase)].wait)
		{
			m_commandQueue->Wait(waitInfo.fence.Get(), waitInfo.value);
		}
		m_commandQueue->ExecuteCommandLists(static_cast<unsigned int>(m_executonPhase[ExecutonPhaseToIndex(executonPhase)].command.size()), m_executonPhase[ExecutonPhaseToIndex(executonPhase)].command.data());
		m_commandQueue->Signal(m_fence.Get(), executonPhase);
	}
}

void Crown::GPUThread::Reset()
{
	m_executonPhase.clear();
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
