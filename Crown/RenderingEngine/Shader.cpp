#include "Shader.h"
#include <filesystem>
#include <d3dcompiler.h>
#include <assert.h>

Crown::Shader::Shader()
{
}

Crown::Shader::~Shader()
{
}

void Crown::Shader::Initialize()
{
	//	シェーダーファイルを探して全て読め込むよ☆
	static const std::wstring searchFileExtension = L".cso";			//	シェーダーファイルの拡張子だよ☆
	for (const std::filesystem::directory_entry& directory : std::filesystem::recursive_directory_iterator(L"./Resource/Shader/"))
	{
		//	取得したファイルパスがシェーダーファイルかどうかを確認☆
		std::wstring filePath = directory.path().wstring();
		if (filePath.find(searchFileExtension) == filePath.length() - static_cast<size_t>(searchFileExtension.size() - 1))
		{
			LoadShader(filePath);	//	シェーダーファイルを読み込み☆
		}
	}
}

ID3DBlob* const Crown::Shader::GetShader(const std::wstring& name)
{
	std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3DBlob>>::iterator data = blob.find(name);	//	データがあるか確認☆
	if (data == blob.end())
	{
		//	なかった！☆
		std::wstring loadFile = L"./Resource/Shader/" + name + L".cso";
		LoadShader(loadFile);	//	読み込みを試みるよ☆

		data = blob.find(name);
		if (data == blob.end())
		{
			assert(0);
			return nullptr;		//	やっぱなかった！☆
		}
	}
	return data->second.Get();	//	あった～☆
}

void Crown::Shader::LoadShader(std::wstring& fileName)
{
	ID3DBlob* LoadBlob = nullptr;									//	シェーダーファイルのデータが入るメモリ領域だよ☆
	struct _stat st;												//	ファイル設定の構造体だよ☆
	_wstat(fileName.data(), &st);									//	ファイル情報の取得だよ☆
	D3DCreateBlob(static_cast<SIZE_T>(st.st_size), &LoadBlob);		//	メモリ領域の確保だよ☆

	//	ファイルが開けるか確認するよ☆
	FILE* file = nullptr;
	_wfopen_s(&file, fileName.data(), L"rb");
	if (file == nullptr)											//	ファイルを開けたのか確認するよ☆
	{
		return;
	}

	fread(LoadBlob->GetBufferPointer(), LoadBlob->GetBufferSize(), 1, file);
	fclose(file);

	//	ファイル名の取得だよ☆
	fileName.erase(fileName.begin(), fileName.begin() + 18);		//	共通のパスを削除するよ☆
	fileName.erase(fileName.end() - 4, fileName.end());				//	拡張子を削除するよ☆
	//	ファイル名の￥を/に変換するよ☆
	fileName.insert(fileName.begin() + fileName.find(L"\\"), L'/');
	fileName.erase(fileName.begin() + fileName.find(L"\\"));

	blob[fileName] = LoadBlob;
}