#pragma once
#ifndef CROWN_GRAPHICS_SHADER
#define CROWN_GRAPHICS_SHADER
//================================================
// 作成日 : 2023/4/27
// 作成者 : 服部颯澄
// 
// C++17以上でのみ動作☆
// 
// シェーダーを扱うクラスだよ☆
// 
//================================================
#include <d3dcompiler.h>
#include <string>
#include <unordered_map>
#include <wrl.h>
#pragma comment(lib,"d3dcompiler.lib")
namespace Crown
{
	namespace RenderObject
	{
		class Shader
		{
		public:
			static Shader* GetInstance();
			static void DeleteInstance();

			ID3DBlob* const GetShader(const std::wstring& name);


		private:
			Shader();
			virtual ~Shader();
			Shader(const Shader& shader) = delete;
			Shader& operator=(const Shader& shader) = delete;
			static Shader* me;

			std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3DBlob>> blob;
			void Initialize();
			void LoadShader(std::wstring& fileName);
			void CompileFile(std::wstring& fileName, ID3DInclude* include, LPCSTR entrypoint, LPCSTR target, UINT flage);
		};
	}
}
#endif // !CROWN_GRAPHICS_SHADER