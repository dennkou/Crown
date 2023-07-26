#include "RenderCommandQueue.h"

Crown::RenderObject::RenderCommand::RenderCommandQueue::RenderCommandQueue()
	:
	loakFlag(false)
{
}

Crown::RenderObject::RenderCommand::RenderCommandQueue::~RenderCommandQueue()
{
}

void Crown::RenderObject::RenderCommand::RenderCommandQueue::AddCommand(RenderCommandBase* command)
{
	std::shared_ptr<RenderCommandBase> newCommand(command);
	m_renderCommands.push_back(newCommand);
}

void Crown::RenderObject::RenderCommand::RenderCommandQueue::Run(GraphicsCommandList& commandList)
{
	for (std::shared_ptr<RenderCommandBase> command : m_renderCommands)
	{
		command->Run(commandList);
	}
}