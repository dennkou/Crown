#include "RenderCommandQueue.h"

Crown::RenderObject::RenderCommand::RenderCommandQueue::RenderCommandQueue()
	:
	m_valid(false)
{
}

Crown::RenderObject::RenderCommand::RenderCommandQueue::RenderCommandQueue(ID3D12Device* device, std::vector<std::shared_ptr<RenderCommandBase>>& renderCommands, const std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>& useResource)
{
	m_valid = true;	//	このコマンドキューは有効☆

	//	使用するリソースの所有権を確保☆
	m_useResource = useResource;

	//	バンドルコマンドリストを作成☆
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_BUNDLE, IID_PPV_ARGS(&m_bundleCommandAllocator));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_BUNDLE, m_bundleCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_bundleCommandList));

	//	コマンドを登録するよ☆
	ID3D12GraphicsCommandList* commandList = m_bundleCommandList.Get();
	for (std::shared_ptr<RenderCommandBase>& renderCommand : renderCommands)
	{
		renderCommand->Run(commandList);
	}
	commandList->Close();	//	登録が終わったのでクローズ☆
}

Crown::RenderObject::RenderCommand::RenderCommandQueue::~RenderCommandQueue()
{
}

void Crown::RenderObject::RenderCommand::RenderCommandQueue::Run(GraphicsCommandList& commandList)
{
	if (!m_valid)
	{
		return;	//	コマンドキューが無効なら処理しない☆
	}
	commandList.GetGraphicsCommandList()->ExecuteBundle(m_bundleCommandList.Get());
	for (Microsoft::WRL::ComPtr<ID3D12Resource>& resource : m_useResource)
	{
		commandList.LockResource(resource);
	}
}