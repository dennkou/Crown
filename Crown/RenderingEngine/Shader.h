#pragma once
#include "DirectX12.h"
#include <unordered_map>


namespace Crown
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Initialize();

		ID3DBlob* const GetShader(const std::wstring& name);
	private:
		void LoadShader(std::wstring& fileName);

		std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3DBlob>> blob;
	};
}