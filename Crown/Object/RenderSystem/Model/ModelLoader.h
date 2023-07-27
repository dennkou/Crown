#pragma once
#ifndef CROWN_RENDEROBJECT_MODELLOADER
#define CROWN_RENDEROBJECT_MODELLOADER
#include "Model.h"

#include "./../DirectX12Wraps/RootSignature.h"
#include "./../DirectX12Wraps/GraphicPipeline.h"
#include "./../TextureBuffer.h"
#include <memory>

namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/7/6
		// 作成者 : 服部颯澄
		// 
		// モデルデータの読み込みを行うクラスだよ☆
		// modelクラスの内、モデルデータの作成部分を分離したものだよ☆
		//
		//================================================
		class Model::ModelLoader
		{
		public:
			enum class LoadFile
			{
				PMD,
			};

			ModelLoader(const std::wstring& fileName, LoadFile loadMode, Model& model);
			~ModelLoader();

			void Load(ID3D12Device* device, TextureBuffer* textureBuffer);
		private:
			/// <summary>
			/// ファイルを開く関数だよ☆
			/// 開けなかったらfalseを返すよ☆
			/// </summary>
			/// <param name="fileName"></param>
			/// <param name="extension"></param>
			/// <param name="file"></param>
			/// <returns></returns>
			bool FileOpen(const std::wstring& fileName, const std::wstring& extension, FILE*& file);

			void LoadPMD(ID3D12Device* device, TextureBuffer* textureBuffer);

			void CreateTestData(ID3D12Device* device);

			Model& m_model;
			std::wstring m_filePath;
			LoadFile m_loadMode;

			static RootSignature rootSignature;
			static GraphicsPipeline graphicsPipeline;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_MODELLOADER