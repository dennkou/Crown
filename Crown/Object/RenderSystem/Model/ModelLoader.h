#pragma once
#ifndef CROWN_RENDEROBJECT_MODELLOADER
#define CROWN_RENDEROBJECT_MODELLOADER
#include "Model.h"
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
				PMX,
			};

			ModelLoader(const std::wstring& fileName, LoadFile loadMode, Model& model);
			~ModelLoader();

			void Load(ID3D12Device* device, TextureBuffer* textureBuffer);
		private:

			Model& m_model;
			std::wstring m_filePath;
			LoadFile m_loadMode;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_MODELLOADER