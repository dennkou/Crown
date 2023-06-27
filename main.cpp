#include <Windows.h>
#include <iostream>
#include "Crown/System.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//	引数は使わないよ☆
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	Crown::System* system = Crown::System::GetInstance();

	system->Initialize();

#ifdef _DEBUG
	// メモリリークチェックのためのデバッグフラグを設定するよ☆
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// レポートモードを設定するよ☆
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // _DEBUG

	while (!system->GetEndFlag())
	{
		system->Update();
	}

	system->Finalize();

	return 0;
}