#include <Windows.h>

#include "Crown/Crown.h"

#include <thread>
#include <iostream>

//	デバック有効化用のインクルード＆defineだよ☆
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//	引数は使わないよ☆
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

#ifdef _DEBUG
	// メモリリークチェックのためのデバッグフラグを設定するよ☆
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// レポートモードを設定するよ☆
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // _DEBUG

	Crown::GameEngine::GetGameEngine().Run(L"Crown");

	return 0;
}