#include "DescriptorHeap.h"

Crown::DescriptorHeap::DescriptorHeap(Microsoft::WRL::ComPtr<ID3D12Device> device)
{
	m_device = device;
	D3D12_DESCRIPTOR_HEAP_DESC DescriptorHeapDesc;
	DescriptorHeapDesc.NodeMask = 1;
	DescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	DescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	DescriptorHeapDesc.NumDescriptors = 1000000;
	m_device->CreateDescriptorHeap(&DescriptorHeapDesc, IID_PPV_ARGS(m_gpuDescriptorHeap.GetAddressOf()));

	//	�f�B�X�N���v�^�����W�̐ݒ肾�恙
	D3D12_DESCRIPTOR_RANGE descriptorRange[4] = {};
	//	�V�[����񂾂恙
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptorRange[0].BaseShaderRegister = 0;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	���f����񂾂恙
	descriptorRange[1].NumDescriptors = 1;
	descriptorRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptorRange[1].BaseShaderRegister = 1;
	descriptorRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	�}�e���A���p�萔���恙
	descriptorRange[2].NumDescriptors = 1;
	descriptorRange[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptorRange[2].BaseShaderRegister = 2;
	descriptorRange[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	�}�e���A���p�e�N�X�`����
	descriptorRange[3].NumDescriptors = 4;
	descriptorRange[3].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[3].BaseShaderRegister = 0;
	descriptorRange[3].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	���[�g�p�����[�^�̍쐬���s���恙
	static const unsigned int parameterNum = 3;
	D3D12_ROOT_PARAMETER rootParameter[parameterNum] = {};

	//	�J������񂾂恙
	rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameter[0].DescriptorTable.pDescriptorRanges = &descriptorRange[0];
	rootParameter[0].DescriptorTable.NumDescriptorRanges = 1;

	//	���f�����p���恙
	rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameter[1].DescriptorTable.pDescriptorRanges = &descriptorRange[1];
	rootParameter[1].DescriptorTable.NumDescriptorRanges = 1;

	//	�}�e���A���p���恙
	rootParameter[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameter[2].DescriptorTable.pDescriptorRanges = &descriptorRange[2];
	rootParameter[2].DescriptorTable.NumDescriptorRanges = 2;

	//	�T���v���[�̐ݒ肾�恙
	const unsigned int samplerNum = 2;
	D3D12_STATIC_SAMPLER_DESC samplerDesc[samplerNum] = {};
	samplerDesc[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	samplerDesc[0].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	samplerDesc[0].Filter = D3D12_FILTER_ANISOTROPIC;
	samplerDesc[0].MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc[0].MinLOD = 0.0f;
	samplerDesc[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	samplerDesc[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc[0].ShaderRegister = 0;

	samplerDesc[1] = samplerDesc[0];//�ύX�_�ȊO���R�s�[
	samplerDesc[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc[1].ShaderRegister = 1;

	//	���[�g�V�O�l�`���[�̐ݒ肾�恙
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParameter;
	rootSignatureDesc.NumParameters = parameterNum;
	rootSignatureDesc.pStaticSamplers = samplerDesc;
	rootSignatureDesc.NumStaticSamplers = samplerNum;

	//	���[�g�V�O�l�`���[���쐬����恙
	ID3DBlob* rootSigBlob = nullptr;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, nullptr);
	device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));	//	���[�g�V�O�l�`���[���쐬����恙
	rootSigBlob->Release();
}

Crown::DescriptorHeap::~DescriptorHeap()
{
}

void Crown::DescriptorHeap::RenderUpdate()
{
}