#pragma once
#ifndef CROWN_RENDEROBJECT_MODELMANAGER
#define CROWN_RENDEROBJECT_MODELMANAGER
#include "MaterialTag.h"
#include <d3d12.h>
#include <vector>
#include "Model.h"
#include "./../TextureBuffer.h"
#include "./../DirectX12Wraps/GraphicsCommandList.h"
namespace Crown
{
	namespace RenderObject
	{
		//================================================
		// 作成日 : 2023/6/28
		// 作成者 : 服部颯澄
		// 
		// モデルの管理を行うクラスだよ☆
		// 
		// 外部で作成されるmodelクラスとライブラリ内部の情報のやり取りを行うよ☆
		// 
		//================================================
		class Model;
		class Model::ModelLoader;
		class ModelManager
		{
		public:
			ModelManager();
			~ModelManager();

			void Initialize(ID3D12Device* device, TextureBuffer* textureBuffer);

			void AddModel(Model* newModel);
			void DeleteModel(Model* deleteModel);

			void Draw(MaterialTag drawTag, GraphicsCommandList& commandList);

			void loadModel(Model::ModelLoader* modelLoader);
		private:
			ID3D12Device* m_device;
			std::vector<Model*> m_models;
			TextureBuffer* m_textureBuffer;
		};
	}
}
#endif // !CROWN_RENDEROBJECT_MODELMANAGER