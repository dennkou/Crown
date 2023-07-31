#include "Pmd.h"
#include "./../../../StringAlgorithm.h"
#include "./../../RenderCommands/RenderCommandFactory.h"
#include "./../../Shader.h"
#include "./../../Camera.h"



Crown::RenderObject::RootSignature* Crown::RenderObject::Pmd::rootSignature = nullptr;
Crown::RenderObject::GraphicsPipeline* Crown::RenderObject::Pmd::graphicsPipeline = nullptr;
const D3D12_INPUT_ELEMENT_DESC Crown::RenderObject::Pmd::inputLayout[5] =
{
	{ "POSITION",	0,DXGI_FORMAT_R32G32B32_FLOAT,	0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 },
	{ "NORMAL",		0,DXGI_FORMAT_R32G32B32_FLOAT,	0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 },
	{ "TEXCOORD",	0,DXGI_FORMAT_R32G32_FLOAT,		0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 },
	{ "BONE_INDEX",	0,DXGI_FORMAT_R32G32_UINT,		0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 },
	{ "WEIGHT",		0,DXGI_FORMAT_R32_FLOAT,		0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0 }
};



void Crown::RenderObject::Pmd::Load(ID3D12Device* device, std::wstring& fileName, TextureBuffer& textureBuffer, Vertices& verticesBuffer, std::vector<MaterialMesh>& materialMeshs, unsigned int descriptorOffset, Microsoft::WRL::ComPtr<ID3D12Resource> resource)
{
	if (rootSignature == nullptr)
	{
		rootSignature = new RootSignature();
		rootSignature->Create(device);
	}
	if (graphicsPipeline == nullptr)
	{
		graphicsPipeline = new GraphicsPipeline();
		graphicsPipeline->SetVS(*Shader::GetInstance()->GetShader(L"PMD/DefaultVertexShader"));
		graphicsPipeline->SetPS(*Shader::GetInstance()->GetShader(L"PMD/DefaultPixelShader"));
		graphicsPipeline->SetRootSignature(rootSignature->GetRootSignature().Get());
		D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
		inputLayoutDesc.pInputElementDescs = inputLayout;
		inputLayoutDesc.NumElements = 5;
		graphicsPipeline->SetInputLayout(inputLayoutDesc);
		graphicsPipeline->Commit(*device);
	}
	FILE* file = nullptr;
	if(fileName.rfind(L"pmd") == -1)
	{
		assert(0);		//	拡張子が違うよ☆
		return;
	}
	_wfopen_s(&file, fileName.data(), L"rb");
	if (!file)
	{
		assert(0);		//	ファイル開けなかったよ☆
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
		fread(&vertices[i].pos, sizeof(DirectX::XMFLOAT3), 1, file);
		fread(&vertices[i].normal, sizeof(DirectX::XMFLOAT3), 1, file);
		fread(&vertices[i].uv, sizeof(DirectX::XMFLOAT2), 1, file);
		fread(&vertices[i].boneIndex[0], sizeof(unsigned short), 1, file);
		fread(&vertices[i].boneIndex[1], sizeof(unsigned short), 1, file);
		fread(&vertices[i].boneWeight, sizeof(unsigned char), 1, file);
		unsigned char edgeFlg;
		fread(&edgeFlg, sizeof(unsigned char), 1, file);
	}
	//	インデックスデータの読み込み☆
	unsigned int indexNum = 0;
	fread(&indexNum, sizeof(unsigned int), 1, file);
	std::vector<unsigned int> indexs(indexNum);
	for (unsigned int i = 0; i < indexNum; ++i)
	{
		fread(&indexs[i], sizeof(unsigned short), 1, file);
	}

	//	頂点バッファーとインデックスバッファーを作成するよ☆
	verticesBuffer.CreateBuffer(device, vertices, indexs);

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
		bufferData.emplace_back(BlobConstBuffer::DataType::Float3);
		//	スペキュラーカラーの読み込み☆
		DirectX::XMFLOAT3 specular;
		fread(&specular, sizeof(DirectX::XMFLOAT3), 1, file);
		bufferData.emplace_back(BlobConstBuffer::DataType::Float);
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
		std::string tmp;
		tmp.resize(20);
		fread(tmp.data(), sizeof(char), 20, file);

		//	トゥーンデータの解析開始～☆
		std::wstring toonTexture;
		toonTexture.resize(37);
		if (toon < 10)
		{
			swprintf_s(toonTexture.data(), 37, L"Resource/Texture/PmdTex/toon%02d.bmp", toon + 1);
		}
		else
		{
			toonTexture = L"グレイグラデーションテクスチャ";
		}

		//	テクスチャデータの解析開始☆
		std::wstring texture = L"白テクスチャ";
		std::wstring sph = L"白テクスチャ";
		std::wstring spa = L"黒テクスチャ";
		std::vector<std::wstring> textureData;							//	データ数だよ☆
		size_t splitter = tmp.find('*');
		if (splitter == -1)
		{
			textureData.push_back(StringAlgorithm::StringToWstring(tmp));
		}
		else
		{
			textureData.push_back(StringAlgorithm::StringToWstring(tmp.substr(0, splitter)));
			textureData.push_back(StringAlgorithm::StringToWstring(tmp.substr(splitter + 1, tmp.length() - splitter - 1)));
		}
		for (size_t i = 0; i < textureData.size(); ++i)
		{
			size_t idx = textureData[i].rfind('.');
			std::wstring extension = textureData[i].substr(idx + 1, textureData[i].length() - idx - 1);

			if (extension.find(L"sph") != -1)
			{
				sph = L"Resource/Texture/PmdTex/" + textureData[i];
			}
			else if (extension.find(L"spa") != -1)
			{
				spa = L"Resource/Texture/PmdTex/" + textureData[i];
			}
			else
			{
				if (!textureData[i].empty())
				{
					texture = L"Resource/Texture/PmdTex/" + textureData[i];
				}
			}
		}

		//	コンスタントバッファのデータ構造を決定＆データ代入☆
		BlobConstBuffer constBuffer(bufferData, device);
		constBuffer.SetParameter(0, diffuse);
		constBuffer.SetParameter(1, alpha);
		constBuffer.SetParameter(2, specular);
		constBuffer.SetParameter(3, specularity);
		constBuffer.SetParameter(4, ambient);

		//	マテリアル描画の仕方を決定☆
		std::vector<std::shared_ptr<RenderCommand::RenderCommandBase>> renderCommands;
		RenderCommand::RenderCommandFactory::CreateSetRootSignature(renderCommands, rootSignature->GetRootSignature());
		RenderCommand::RenderCommandFactory::CreateSetPrimitiveTopology(renderCommands, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		RenderCommand::RenderCommandFactory::CreateSetVertexBuffer(renderCommands, 0, 1, verticesBuffer.GetVertexBufferView());
		RenderCommand::RenderCommandFactory::CreateSetIndexBuffer(renderCommands, verticesBuffer.GetIndexBufferView());
		RenderCommand::RenderCommandFactory::CreateSetDescriptorHeap(renderCommands);
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 0, Camera::GetInstance()->GetDescriptorOffset());
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 1, descriptorOffset);
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 2, constBuffer.GetDescriptorOffset());
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 3, textureBuffer.TextureAcquisition(texture));
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 4, textureBuffer.TextureAcquisition(sph));
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 5, textureBuffer.TextureAcquisition(spa));
		RenderCommand::RenderCommandFactory::CreateSetDescriptor(renderCommands, 6, textureBuffer.TextureAcquisition(toonTexture));
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> resources;
		resources.emplace_back(verticesBuffer.GetConstVertexBuffer());
		resources.emplace_back(verticesBuffer.GetConstIndexBuffer());
		resources.emplace_back(Camera::GetInstance()->GetConstConstBuffer());
		resources.emplace_back(resource);
		resources.emplace_back(constBuffer.GetBuffer());
		resources.emplace_back(textureBuffer.GetTextureBuffer(textureBuffer.TextureAcquisition(texture)));
		resources.emplace_back(textureBuffer.GetTextureBuffer(textureBuffer.TextureAcquisition(sph)));
		resources.emplace_back(textureBuffer.GetTextureBuffer(textureBuffer.TextureAcquisition(spa)));
		resources.emplace_back(textureBuffer.GetTextureBuffer(textureBuffer.TextureAcquisition(toonTexture)));
		RenderCommand::RenderCommandFactory::CreateSetPipelineState(renderCommands, graphicsPipeline->GetPipelineState());
		RenderCommand::RenderCommandQueue pmdRenderCommandQueue(device, renderCommands, resources);

		//	定数配列を作成☆
		std::vector<BlobConstBuffer> constbuffers;
		constbuffers.push_back(constBuffer);

		//	マテリアルを適用するメッシュデータの作成を行うよ☆
		materialMeshs.emplace_back(materialIndexNum, materialIndexOffset);
		materialIndexOffset += materialIndexNum;
		materialMeshs.back().GetMaterial(MaterialTag::Normal).CreateData(pmdRenderCommandQueue, constbuffers);
	}
}