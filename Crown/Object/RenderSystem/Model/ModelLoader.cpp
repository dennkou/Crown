#include "ModelLoader.h"
#include "./Vertices.h"
#include <vector>
#include <string>
#include "./../RenderCommands/RenderCommandFactory.h"
#include "./../DirectX12Wraps/RootSignature.h"
#include "./../Shader.h"
#include "./../Camera.h"


Crown::RenderObject::RootSignature Crown::RenderObject::Model::ModelLoader::rootSignature;
Crown::RenderObject::GraphicsPipeline Crown::RenderObject::Model::ModelLoader::graphicsPipeline;



Crown::RenderObject::Model::ModelLoader::ModelLoader(const std::wstring& fileName, LoadFile loadMode, Model& model)
	:
	m_filePath(fileName),
	m_loadMode(loadMode),
	m_model(model)
{
}

Crown::RenderObject::Model::ModelLoader::~ModelLoader()
{

}

void Crown::RenderObject::Model::ModelLoader::Load(ID3D12Device* device, TextureBuffer* textureBuffer)
{
	if (rootSignature.GetRootSignature() == nullptr)
	{
		rootSignature.Create(device);
	}
	if (graphicsPipeline.GetPipelineState() == nullptr)
	{
		graphicsPipeline.SetVS(*Shader::GetInstance()->GetShader(L"PMD/DefaultVertexShader"));
		graphicsPipeline.SetPS(*Shader::GetInstance()->GetShader(L"PMD/DefaultPixelShader"));
		graphicsPipeline.SetRootSignature(rootSignature.GetRootSignature().Get());
	}
	switch (m_loadMode)
	{
		case Crown::RenderObject::Model::ModelLoader::LoadFile::PMD:
			LoadPMD(device, textureBuffer);
			break;
		default:
			__assume(0);
			break;
	}
}



void Crown::RenderObject::Model::ModelLoader::LoadPMD(ID3D12Device* device, TextureBuffer* textureBuffer)
{
	FILE* file = nullptr;
	if (!FileOpen(m_filePath, L"pmd", file))
	{
		assert(0);		//	ファイル開けなかったら報告するよ☆
		return;
	}

	//	ヘッダの読み込みだよ☆

	//	pmd形式か確認するよ☆
	{
		static const unsigned int SIGNATURE_NUM = 3;
		char signature[SIGNATURE_NUM] = {};
		char pmd[3] = { 'P','m','d' };
		fread(signature, sizeof(signature), 1, file);
		if (!(signature[0] == pmd[0] && signature[1] == pmd[1] && signature[2] == pmd[2]))
		{
			assert(0);
			return;
		}
	}
	//	バージョンを確認するよ☆
	{
		float version = 0.0f;
		fread(&version, sizeof(float), 1, file);
	}
	//	モデル名のスキップ☆
	{
		static const unsigned int MAX_MODEL_NAME = 20;
		std::string modelName = {};
		modelName.resize(MAX_MODEL_NAME);
		fread((void*)modelName.data(), sizeof(char), MAX_MODEL_NAME, file);
	}
	//	コメントをスキップ☆
	{
		static const unsigned int MAX_COMMENT_NUM = 256;
		std::string comment;
		comment.resize(MAX_COMMENT_NUM);
		fread((void*)comment.data(), sizeof(char), MAX_COMMENT_NUM, file);
	}

	//	ヘッダの読み込み終了～☆

	//	頂点を読み込み☆
	unsigned int vertexNum = 0;
	fread(&vertexNum, sizeof(vertexNum), 1, file);
	std::vector<Vertices::VerticesData> vertices(vertexNum);
	for (unsigned int i = 0; i < vertexNum; ++i)
	{
		fread(&vertices[i].pos,			sizeof(DirectX::XMFLOAT3),	1, file);
		fread(&vertices[i].normal,		sizeof(DirectX::XMFLOAT3),	1, file);
		fread(&vertices[i].uv,			sizeof(DirectX::XMFLOAT2),	1, file);
		fread(&vertices[i].boneIndex[0],sizeof(unsigned short),		1, file);
		fread(&vertices[i].boneIndex[1],sizeof(unsigned short),		1, file);
		fread(&vertices[i].boneWeight,	sizeof(unsigned char),		1, file);
		unsigned char edgeFlg;
		fread(&edgeFlg,						sizeof(unsigned char),		1, file);
	}
	//	インデックスデータの読み込み☆
	unsigned int indexNum = 0;
	fread(&indexNum, sizeof(unsigned int), 1, file);
	std::vector<unsigned int> indexs(indexNum);
	for (unsigned int i = 0; i < indexNum; ++i)
	{
		fread(&indexs[i], sizeof(unsigned short), 1, file);
	}

	//	テストコード☆
	vertices[0].pos = DirectX::XMFLOAT3(-0.4f, -0.7f, 0.0f);
	vertices[1].pos = DirectX::XMFLOAT3(-0.4f, 0.7f, 0.0f);
	vertices[2].pos = DirectX::XMFLOAT3(0.4f, -0.7f, 0.0f);
	vertices[3].pos = DirectX::XMFLOAT3(0.4f, 0.7f, 0.0f);

	indexs[0] = 0;
	indexs[1] = 1;
	indexs[2] = 2;
	indexs[3] = 2;
	indexs[4] = 1;
	indexs[5] = 3;

	//	頂点バッファーとインデックスバッファーを作成するよ☆
	m_model.m_vertices.CreateBuffer(device, vertices, indexs);

	//	マテリアルの読み込みだよ☆
	unsigned int materialNum = 0;
	fread(&materialNum, sizeof(unsigned int), 1, file);
	unsigned int materialIndexOffset = 0;
	for (unsigned int i = 0; i < materialNum; ++i)
	{
		std::vector<BlobConstBuffer::DataType> bufferData;	//	データ構造を指定する配列だよ☆
		//	ディフューズカラーの読み込み☆
		DirectX::XMFLOAT3 diffuse;
		fread(&diffuse, sizeof(DirectX::XMFLOAT3), 1, file);
		bufferData.emplace_back(BlobConstBuffer::DataType::Float3);
		//	ディフューズアルファの読み込み☆
		float alpha;
		fread(&alpha, sizeof(float), 1, file);
		bufferData.emplace_back(BlobConstBuffer::DataType::Float);
		//	スペキュラーパワーの読み込み☆
		float specularity;
		fread(&specularity, sizeof(float), 1, file);
		bufferData.emplace_back(BlobConstBuffer::DataType::Float);
		//	スペキュラーカラーの読み込み☆
		DirectX::XMFLOAT3 specular;
		fread(&specular, sizeof(DirectX::XMFLOAT3), 1, file);
		bufferData.emplace_back(BlobConstBuffer::DataType::Float3);
		//	アンビエントカラーの読み込み☆
		DirectX::XMFLOAT3 ambient;
		fread(&ambient, sizeof(DirectX::XMFLOAT3), 1, file);
		bufferData.emplace_back(BlobConstBuffer::DataType::Float3);
		//	トーンインデックスの読み込み☆
		unsigned char toon;
		fread(&toon, sizeof(unsigned char), 1, file);
		//	エッジフラグの読み込み☆
		bool edgeFlag = false;
		fread(&edgeFlag, sizeof(unsigned char), 1, file);
		//	マテリアルのインデックス数の読み込み☆
		unsigned int materialIndexNum = 0;
		fread(&materialIndexNum, sizeof(unsigned int), 1, file);
		//	テクスチャデータの読み込み☆
		std::string texture;
		texture.resize(20);
		fread(texture.data(), sizeof(char), 20, file);

		//	コンスタントバッファのデータ構造を決定＆データ代入☆
		BlobConstBuffer constBuffer(bufferData, device);
		constBuffer.SetParameter(0, diffuse);
		constBuffer.SetParameter(1, alpha);
		constBuffer.SetParameter(2, specularity);
		constBuffer.SetParameter(3, specular);
		constBuffer.SetParameter(4, ambient);

		//	PSOがなければ生成☆
		if (graphicsPipeline.GetPipelineState() == nullptr)
		{
			graphicsPipeline.SetInputLayout(m_model.m_vertices.GetInputLayoutDesc());
			graphicsPipeline.Commit(*device);
		}

		//	マテリアル描画の仕方を決定☆
		RenderCommand::RenderCommandQueue pmdRenderCommandQueue;
		RenderCommand::RenderCommandFactory::CreateSetRootSignature(pmdRenderCommandQueue, rootSignature.GetRootSignature());
		RenderCommand::RenderCommandFactory::CreateSetPrimitiveTopology(pmdRenderCommandQueue, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		RenderCommand::RenderCommandFactory::CreateSetVertexBuffer(pmdRenderCommandQueue, 0, 1, m_model.m_vertices.GetVertexBufferView(), m_model.m_vertices.GetConstVertexBuffer());
		RenderCommand::RenderCommandFactory::CreateSetIndexBuffer(pmdRenderCommandQueue, m_model.m_vertices.GetIndexBufferView(), m_model.m_vertices.GetConstIndexBuffer());
		RenderCommand::RenderCommandFactory::CreateSetDescriptorHeap(pmdRenderCommandQueue);
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(pmdRenderCommandQueue, 0, Camera::GetInstance()->GetDescriptorOffset(), Camera::GetInstance()->GetConstConstBuffer());
		//RenderCommand::RenderCommandFactory::CreateSetDescriptor(pmdRenderCommandQueue, 2, constBuffer.GetDescriptorOffset());
		//RenderCommand::RenderCommandFactory::CreateSetDescriptor(pmdRenderCommandQueue, 4, textureBuffer->TextureAcquisition(L"黒テクスチャ"));
		RenderCommand::RenderCommandFactory::CreateSetPipelineState(pmdRenderCommandQueue, graphicsPipeline.GetPipelineState());

		//	定数配列を作成☆
		std::vector<BlobConstBuffer> constbuffers;
		constbuffers.push_back(constBuffer);

		//	マテリアルを適用するメッシュデータの作成を行うよ☆
		m_model.m_materialMeshs.emplace_back(materialIndexNum, materialIndexOffset);
		materialIndexOffset += materialIndexNum;
		m_model.m_materialMeshs.back().GetMaterial(MaterialTag::Normal).CreateData(pmdRenderCommandQueue, constbuffers);
	}
}

void Crown::RenderObject::Model::ModelLoader::CreateTestData(ID3D12Device* device)
{

}

bool Crown::RenderObject::Model::ModelLoader::FileOpen(const std::wstring& fileName, const std::wstring& extension, FILE*& file)
{
	if (fileName.rfind(extension) == -1)
	{
		return false;	//	拡張子が違う☆
	}
	_wfopen_s(&file, fileName.data(), L"rb");

	return file;		//	ファイルオープンに成功したかを返しているよ☆
}