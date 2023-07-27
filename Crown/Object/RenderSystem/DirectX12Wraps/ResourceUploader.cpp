#include "ResourceUploader.h"
#include <cassert> 



Crown::RenderObject::ResourceUploader* Crown::RenderObject::ResourceUploader::me = nullptr;



Crown::RenderObject::ResourceUploader::ResourceUploader()
	:
	m_commandList(nullptr),
	m_device(nullptr)
{
}

Crown::RenderObject::ResourceUploader::~ResourceUploader()
{
}

void Crown::RenderObject::ResourceUploader::CreateResourceUploader(ID3D12Device* device, GraphicsCommandList& commandList)
{
	if (me == nullptr)
	{
		me = new ResourceUploader();
		me->m_device = device;
		me->m_commandList = &commandList;
	}
}

Crown::RenderObject::ResourceUploader* Crown::RenderObject::ResourceUploader::GetInstance()
{
	assert(me);
	return me;
}

void Crown::RenderObject::ResourceUploader::DeleteInstance()
{
	delete me;
}

void Crown::RenderObject::ResourceUploader::DeleteUploadResource()
{
}