#include "GraphicsCommandList.h"

Crown::RenderObject::GraphicsCommandList::GraphicsCommandList()
	:
	m_graphicsCommandList(nullptr),
	m_copyCommandList(nullptr),
	m_commandQueue(nullptr),
	m_waitEvent(nullptr),
	m_index(0),
	m_copyIndex(0),
	m_addCommandAllocatorNum(0),
	MAX_FAILEDPROCESSING_NUM(0),
	m_failedProcessingNum(0),
	m_device(nullptr)
{

}

Crown::RenderObject::GraphicsCommandList::~GraphicsCommandList()
{
	RunAndWait();
	m_graphicsCommandList->Close();
	m_copyCommandList->Close();
	CloseHandle(m_waitEvent);
}

void Crown::RenderObject::GraphicsCommandList::Initialize(ID3D12Device* device, unsigned int allocatorNum,  unsigned int failedProcessingNum)
{
	//	バッファー数が必ず1以上になるようにするよ☆
	if (allocatorNum < 1)
	{
		allocatorNum = 1;
	}
	m_device = device;
	const_cast<unsigned int&>(MAX_FAILEDPROCESSING_NUM) = failedProcessingNum;
	m_waitEvent = CreateEvent(nullptr, false, false, nullptr);	//	イベントを作成するよ☆
	m_addCommandAllocatorNum = allocatorNum - 1;

	m_commandAllocators.emplace_back(new CommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT));
	device->CreateCommandList(1, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators.front()->GetCommandAllocator(), nullptr, IID_PPV_ARGS(&m_graphicsCommandList));	//	コマンドリストの作成だよ☆

	m_copyAllocators.emplace_back(new CommandAllocator(device, D3D12_COMMAND_LIST_TYPE_DIRECT));
	device->CreateCommandList(1, D3D12_COMMAND_LIST_TYPE_DIRECT, m_copyAllocators.front()->GetCommandAllocator(), nullptr, IID_PPV_ARGS(&m_copyCommandList));

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;																						//	タイムアウトなしだよ☆
	cmdQueueDesc.NodeMask = 0;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;																				//	高い優先度を指定するよ☆
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;																						//	コマンドリストのタイプはダイレクトコマンドリストだよ☆
	device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_commandQueue));																//	コマンドキュー生成だよ☆
}

void Crown::RenderObject::GraphicsCommandList::WaitForGpu() noexcept
{
	for (std::unique_ptr<CommandAllocator>& allocator : m_commandAllocators)
	{
		allocator->WaitForGpu(m_waitEvent);
	}
}

void Crown::RenderObject::GraphicsCommandList::RunCommandList()
{
	Run();
	NextCommandAllocator();
	m_commandAllocators[m_index]->Reset();
	m_graphicsCommandList->Reset(m_commandAllocators[m_index]->GetCommandAllocator(), nullptr);
}

void Crown::RenderObject::GraphicsCommandList::RunAndWait()
{
	Run();
	m_commandAllocators[m_index]->WaitForGpu(m_waitEvent);
	m_commandAllocators[m_index]->Reset();
	m_graphicsCommandList->Reset(m_commandAllocators[m_index]->GetCommandAllocator(), nullptr);
}

void Crown::RenderObject::GraphicsCommandList::Run()
{
	{
		m_copyCommandList->Close();																									//	コピー用コマンドリストをクローズ☆
		ID3D12CommandList* cmdlists[] = { m_copyCommandList.Get()};
		m_commandQueue->ExecuteCommandLists(1, cmdlists);																			//	コマンドリストの内容を実行するよ☆
		m_copyAllocators[m_copyIndex]->CountUp();
		m_commandQueue->Signal(m_copyAllocators[m_copyIndex]->GetFence(), m_copyAllocators[m_copyIndex]->GetFenceValue());
		for (unsigned int i = 0, size = static_cast<unsigned int>(m_copyAllocators.size()); i <= size; ++i)
		{
			if (i == size)
			{
				m_copyAllocators.emplace_back(new CommandAllocator(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT));
			}
			if (!m_copyAllocators[i]->NotDrewEnd())
			{
				m_copyIndex = i;
				break;
			}
		}
		m_copyAllocators[m_copyIndex]->Reset();
		m_copyCommandList->Reset(m_copyAllocators[m_copyIndex]->GetCommandAllocator(), nullptr);
	}
	{
		m_graphicsCommandList->Close();																								//	コマンドリストをクローズ☆以降このコマンドリストは命令を受け付けないよ☆
		ID3D12CommandList* cmdlists[] = { m_graphicsCommandList.Get()};
		m_commandQueue->ExecuteCommandLists(1, cmdlists);																			//	コマンドリストの内容を実行するよ☆
		m_commandAllocators[m_index]->CountUp();
		m_commandQueue->Signal(m_commandAllocators[m_index]->GetFence(), m_commandAllocators[m_index]->GetFenceValue());
	}
}

void Crown::RenderObject::GraphicsCommandList::NextCommandAllocator()
{
	//	次に実行使うコマンドアロケーターを探すよ☆
	for (int i = 0, size = static_cast<int>(m_commandAllocators.size()); i < size; ++i)
	{
		//	コマンドアロケーターの中から処理が終わっているものを探すよ☆
		if (!m_commandAllocators[i]->NotDrewEnd())
		{
			//	処理が終っているのでこのコマンドアロケーターを次に使用することとするよ☆
			m_index = i;
			m_failedProcessingNum = 0;
			return;
		}
	}

	//	使えるコマンドアロケーターが無いので処理落ちが発生したと判定するよ☆
	++m_failedProcessingNum;

	//	処理落ちが許可されたフレーム数より多く発生している？
	if (MAX_FAILEDPROCESSING_NUM < m_failedProcessingNum)
	{
		if (m_addCommandAllocatorNum > 0)
		{
			--m_addCommandAllocatorNum;																			//	現在許可されたアロケーターの数を減らすよ☆
			m_index = static_cast<int>(m_commandAllocators.size());												//	追加されるコマンドアロケーターを次に使用することとするよ☆
			m_commandAllocators.emplace_back(new CommandAllocator(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT));	//	コマンドアロケーターを追加するよ☆
			m_failedProcessingNum = 0;																			//	処理落ちを回避したよ☆
			return;
		}
	}

	++m_index;
	m_index %= m_commandAllocators.size();
	m_commandAllocators[m_index]->WaitForGpu(m_waitEvent);
}