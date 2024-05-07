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
	//	�V�F�[�_�[�t�@�C����T���đS�ēǂߍ��ނ恙
	static const std::wstring searchFileExtension = L".cso";			//	�V�F�[�_�[�t�@�C���̊g���q���恙
	for (const std::filesystem::directory_entry& directory : std::filesystem::recursive_directory_iterator(L"./Resource/Shader/"))
	{
		//	�擾�����t�@�C���p�X���V�F�[�_�[�t�@�C�����ǂ������m�F��
		std::wstring filePath = directory.path().wstring();
		if (filePath.find(searchFileExtension) == filePath.length() - static_cast<size_t>(searchFileExtension.size() - 1))
		{
			LoadShader(filePath);	//	�V�F�[�_�[�t�@�C����ǂݍ��݁�
		}
	}
}

ID3DBlob* const Crown::Shader::GetShader(const std::wstring& name)
{
	std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3DBlob>>::iterator data = blob.find(name);	//	�f�[�^�����邩�m�F��
	if (data == blob.end())
	{
		//	�Ȃ������I��
		std::wstring loadFile = L"./Resource/Shader/" + name + L".cso";
		LoadShader(loadFile);	//	�ǂݍ��݂����݂�恙

		data = blob.find(name);
		if (data == blob.end())
		{
			assert(0);
			return nullptr;		//	����ςȂ������I��
		}
	}
	return data->second.Get();	//	�������`��
}

void Crown::Shader::LoadShader(std::wstring& fileName)
{
	ID3DBlob* LoadBlob = nullptr;									//	�V�F�[�_�[�t�@�C���̃f�[�^�����郁�����̈悾�恙
	struct _stat st;												//	�t�@�C���ݒ�̍\���̂��恙
	_wstat(fileName.data(), &st);									//	�t�@�C�����̎擾���恙
	D3DCreateBlob(static_cast<SIZE_T>(st.st_size), &LoadBlob);		//	�������̈�̊m�ۂ��恙

	//	�t�@�C�����J���邩�m�F����恙
	FILE* file = nullptr;
	_wfopen_s(&file, fileName.data(), L"rb");
	if (file == nullptr)											//	�t�@�C�����J�����̂��m�F����恙
	{
		return;
	}

	fread(LoadBlob->GetBufferPointer(), LoadBlob->GetBufferSize(), 1, file);
	fclose(file);

	//	�t�@�C�����̎擾���恙
	fileName.erase(fileName.begin(), fileName.begin() + 18);		//	���ʂ̃p�X���폜����恙
	fileName.erase(fileName.end() - 4, fileName.end());				//	�g���q���폜����恙
	//	�t�@�C�����́���/�ɕϊ�����恙
	fileName.insert(fileName.begin() + fileName.find(L"\\"), L'/');
	fileName.erase(fileName.begin() + fileName.find(L"\\"));

	blob[fileName] = LoadBlob;
}