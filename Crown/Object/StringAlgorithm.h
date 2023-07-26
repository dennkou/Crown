#pragma once
#ifndef CROWN_STRING_ALGORITHM
#define CROWN_STRING_ALGORITHM
//================================================
// 作成日 : 2023/6/14
// 作成者 : 服部颯澄
// 
// string,wstringに関係するアルゴリズムを提供するクラスだよ☆
// 
//================================================
#include <string>
#include <Windows.h>
namespace Crown
{
	class StringAlgorithm
	{
	public:
		/// <summary>
		/// stringをwstringに変換するよ☆
		/// </summary>
		static std::wstring StringToWstring(std::string str)
		{
			//	文字数を取得するよ☆
			int num1 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.c_str(), -1, nullptr, 0);
			std::wstring wstr;
			wstr.resize(num1);//	得られた文字列数でリサイズするよ☆
			//	変換するよ☆
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.c_str(), -1, &wstr[0], num1);
			//	終端文字を削除するよ☆
			if (wstr.back() == 0)
			{
				wstr.pop_back();
			}
			return wstr;
		};
		/// <summary>
		/// wstringをstringに変換するよ☆
		/// </summary>
		static std::string WstringToString(std::wstring wstr)
		{
			//	文字数を取得するよ☆
			int num = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
			std::string str;
			str.resize(num);//	得られた文字列数でリサイズするよ☆
			//	変換するよ☆
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], num, nullptr, nullptr);
			return str;
		};
	};
}
#endif // !CROWN_STRING_ALGORITHM