#include "Shader.h"
#include <sys/stat.h>
#include <filesystem>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


Crown::RenderObject::Shader* Crown::RenderObject::Shader::me = nullptr;

Crown::RenderObject::Shader::Shader()
	:
	blob()
{
	Initialize();
}

Crown::RenderObject::Shader::~Shader()
{
	for (std::pair<const std::wstring, Microsoft::WRL::ComPtr<ID3DBlob>>& deleteBlob : blob)
	{
		deleteBlob.second->Release();
	}
}

Crown::RenderObject::Shader* Crown::RenderObject::Shader::GetInstance()
{
	if (me == nullptr)
	{
		me = new Shader();
	}
	return me;
}

void Crown::RenderObject::Shader::DeleteInstance()
{
	if (me != nullptr)
	{
		delete me;
		me = nullptr;
	}
}

ID3DBlob *const Crown::RenderObject::Shader::GetShader(const std::wstring& name)
{
	std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3DBlob>>::iterator data = blob.find(name);	//	データがあるか確認☆
	if (data == blob.end())
	{
		//	なかった！☆
		std::wstring loadFile = name;
		LoadShader(loadFile);	//	読み込みを試みるよ☆

		data = blob.find(name);
		if (data == blob.end())
		{
			return nullptr;		//	やっぱなかった！☆
		}
		return data->second.Get();	//	あった～☆
	}
	return data->second.Get();
}





//==================================================================================================================================





void Crown::RenderObject::Shader::Initialize()
{
	//	シェーダーファイルを探して全て読め込むよ☆
	static const unsigned int searchFileExtensionSize = 5;
	static const wchar_t searchFileExtension[searchFileExtensionSize] = L".cso";			//	シェーダーファイルの拡張子だよ☆
	static const wchar_t searchDirectory[19] = L"./Resource/Shader/";						//	シェーダーファイルを探すファイルパスだよ☆
	for (const std::filesystem::directory_entry& directory : std::filesystem::recursive_directory_iterator(searchDirectory))
	{
		//	取得したファイルパスがシェーダーファイルかどうかを確認☆
		std::wstring filePath = directory.path().wstring();
		if (filePath.find(searchFileExtension) == filePath.length() - static_cast<size_t>(searchFileExtensionSize - 1))
		{
			LoadShader(filePath);	//	シェーダーファイルを読み込み☆
		}
	}
}

void Crown::RenderObject::Shader::LoadShader(std::wstring& fileName)
{
	//	ファイルが開けるか確認するよ☆
	FILE* file = nullptr;
	_wfopen_s(&file, fileName.data(), L"rb");
	if (file == nullptr)											//	ファイルを開けたのか確認するよ☆
	{
		return;
	}

	ID3DBlob* LoadBlob = nullptr;									//	シェーダーファイルのデータが入るメモリ領域だよ☆
	struct _stat st;												//	ファイル設定の構造体だよ☆
	_wstat(fileName.data(), &st);									//	ファイル情報の取得だよ☆

	D3DCreateBlob(static_cast<SIZE_T>(st.st_size), &LoadBlob);		//	メモリ領域の確保だよ☆

	fread(LoadBlob->GetBufferPointer(), LoadBlob->GetBufferSize(), 1, file);
	fclose(file);

	//	ファイル名の取得だよ☆
	fileName.erase(fileName.begin(), fileName.begin() + 18);		//	共通のパスを削除するよ☆
	fileName.erase(fileName.end() - 4, fileName.end());				//	拡張子を削除するよ☆
	//	ファイル名の￥を/に変換するよ☆
	fileName.insert(fileName.begin() + fileName.find(L"\\"),L'/');
	fileName.erase(fileName.begin() + fileName.find(L"\\"));

	blob[fileName] = LoadBlob;
}



void Crown::RenderObject::Shader::CompileFile(std::wstring& fileName, ID3DInclude* include, LPCSTR entrypoint, LPCSTR target, UINT flage)
{
	ID3DBlob* CompileBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	if (S_OK != D3DCompileFromFile(fileName.data(), nullptr, include, entrypoint, target, flage, 0, &CompileBlob, &errorBlob))
	{
#ifdef _DEBUG
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		std::cout << errstr.c_str() << std::endl;
#endif // _DEBUG
	}
}
