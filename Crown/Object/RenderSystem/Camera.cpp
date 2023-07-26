#include "Camera.h"
#include "DirectX12Wraps/ResourceUploader.h"
#include "RenderCommands/RenderCommandFactory.h"
#include "DirectX12Wraps/DescriptorHeaps.h"
#include <d3dx12.h>

Crown::RenderObject::Camera* Crown::RenderObject::Camera::me = nullptr;

Crown::RenderObject::Camera::Camera()
	:
	m_descriptorOffset(0)
{

}

Crown::RenderObject::Camera::~Camera()
{

}

void Crown::RenderObject::Camera::CreateInstance(ID3D12Device* device)
{
	if (me == nullptr)
	{
		me = new Camera();

		D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(ResourceUploader::GetInstance()->Get255AlignmentSize<CameraData>());
		device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&me->m_resource));
		me->DataUpload();

		//	ディスクリプタの作成を行うよ☆
		D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferViewDesc = {};
		constantBufferViewDesc.BufferLocation = me->m_resource->GetGPUVirtualAddress();
		constantBufferViewDesc.SizeInBytes = ResourceUploader::GetInstance()->Get255AlignmentSize<CameraData>();
		me->m_descriptorOffset = DescriptorHeaps::GetInstance().CreateConstantBufferView(constantBufferViewDesc);
	}
}

Crown::RenderObject::Camera* Crown::RenderObject::Camera::GetInstance()
{
	assert(me);
	return me;
}

void Crown::RenderObject::Camera::DelteInstance()
{
	delete me;
}

void Crown::RenderObject::Camera::SetView(DirectX::XMMATRIX view)
{
	m_cpuSideCameraData.view = view;
	m_cpuSideCameraData.viewProjection = view * m_cpuSideCameraData.projection;
	this->DataUpload();
}