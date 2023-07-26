#include "RootSignature.h"

Crown::RenderObject::RootSignature::RootSignature()
{
}

Crown::RenderObject::RootSignature::~RootSignature()
{
}

void Crown::RenderObject::RootSignature::Create(ID3D12Device* device)
{
	//	ディスクリプタレンジの設定だよ☆
	D3D12_DESCRIPTOR_RANGE descriptorRange[7] = {};

	//	カメラ情報だよ☆
	descriptorRange[0].NumDescriptors = 1;
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptorRange[0].BaseShaderRegister = 0;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	モデル情報用だよ☆
	descriptorRange[1].NumDescriptors = 1;
	descriptorRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptorRange[1].BaseShaderRegister = 1;
	descriptorRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	マテリアル用定数だよ☆
	descriptorRange[2].NumDescriptors = 1;
	descriptorRange[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	descriptorRange[2].BaseShaderRegister = 2;
	descriptorRange[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	マテリアル用テクスチャ☆
	descriptorRange[3].NumDescriptors = 1;
	descriptorRange[3].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[3].BaseShaderRegister = 0;
	descriptorRange[3].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	descriptorRange[4].NumDescriptors = 1;
	descriptorRange[4].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[4].BaseShaderRegister = 1;
	descriptorRange[4].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	descriptorRange[5].NumDescriptors = 1;
	descriptorRange[5].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[5].BaseShaderRegister = 2;
	descriptorRange[5].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	descriptorRange[6].NumDescriptors = 1;
	descriptorRange[6].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange[6].BaseShaderRegister = 3;
	descriptorRange[6].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//	ルートパラメータの作成を行うよ☆
	static const unsigned int parameterNum = 7;
	D3D12_ROOT_PARAMETER rootParameter[parameterNum] = {};

	//	カメラ情報だよ☆
	rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameter[0].DescriptorTable.pDescriptorRanges = &descriptorRange[0];
	rootParameter[0].DescriptorTable.NumDescriptorRanges = 1;

	//	モデル情報用だよ☆
	rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameter[1].DescriptorTable.pDescriptorRanges = &descriptorRange[1];
	rootParameter[1].DescriptorTable.NumDescriptorRanges = 1;

	//	マテリアル用だよ☆
	rootParameter[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameter[2].DescriptorTable.pDescriptorRanges = &descriptorRange[2];
	rootParameter[2].DescriptorTable.NumDescriptorRanges = 1;

	rootParameter[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameter[3].DescriptorTable.pDescriptorRanges = &descriptorRange[3];
	rootParameter[3].DescriptorTable.NumDescriptorRanges = 1;

	rootParameter[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameter[4].DescriptorTable.pDescriptorRanges = &descriptorRange[4];
	rootParameter[4].DescriptorTable.NumDescriptorRanges = 1;

	rootParameter[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameter[5].DescriptorTable.pDescriptorRanges = &descriptorRange[5];
	rootParameter[5].DescriptorTable.NumDescriptorRanges = 1;

	rootParameter[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameter[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rootParameter[6].DescriptorTable.pDescriptorRanges = &descriptorRange[6];
	rootParameter[6].DescriptorTable.NumDescriptorRanges = 1;

	//	サンプラーの設定だよ☆
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

	samplerDesc[1] = samplerDesc[0];//変更点以外をコピー
	samplerDesc[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	samplerDesc[1].ShaderRegister = 1;

	//	ルートシグネチャーの設定だよ☆
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParameter;
	rootSignatureDesc.NumParameters = parameterNum;
	rootSignatureDesc.pStaticSamplers = samplerDesc;
	rootSignatureDesc.NumStaticSamplers = samplerNum;

	//	ルートシグネチャーを作成するよ☆
	ID3DBlob* rootSigBlob = nullptr;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, nullptr);
	device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));	//	ルートシグネチャーを作成するよ☆
	rootSigBlob->Release();
}