#include "Window.h"

#include "Window.h"
#include <tchar.h>

//	デフォルトのスクリーンサイズだよ☆
#define DEFAULT_WINDOW_WIDTH	1920
#define DEFAULT_WINDOW_HEIGHT	1080

Crown::Window::Window()
	:
	m_width(DEFAULT_WINDOW_WIDTH),
	m_height(DEFAULT_WINDOW_HEIGHT),
	m_hwnd(0),
	m_endFlag(false)
{

}

Crown::Window::~Window()
{

}

void Crown::Window::MakeWindow(std::wstring windowName, WNDPROC windowProcedure, DWORD dwStyle)
{
	WNDCLASSEX w = {};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = windowProcedure;			//	ウィンドウプロージャの指定だよ☆
	w.lpszClassName = windowName.data();		//	アプリケーションの名前だよ☆
	w.hInstance = GetModuleHandle(0);			//	アプリケーションハンドルの指定だよ☆

	RegisterClassEx(&w);						//	ウィンドウクラスを登録するよ☆

	RECT wrc = { 0,0, m_width, m_height };		//	ウィンドウサイズを決めるよ☆
	AdjustWindowRect(&wrc, dwStyle, false);		//	クライアントサイズからウィンドウサイズを計算するよ☆
	//ウィンドウオブジェクトの生成
	m_hwnd = CreateWindow
	(
		windowName.data(),						//	クラス名指定だよ☆
		windowName.data(),						//	タイトルバーの文字だよ☆
		dwStyle,								//	ウィンドウタイプを指定されたものに☆
		CW_USEDEFAULT,							//	表示X座標はOSに任せるよ☆
		CW_USEDEFAULT,							//	表示Y座標はOSに任せるよ☆
		wrc.right - wrc.left,					//	ウィンドウ幅の指定だよ☆
		wrc.bottom - wrc.top,					//	ウィンドウ高の指定だよ☆
		nullptr,								//	親ウィンドウハンドルはないよ☆
		nullptr,								//	メニューハンドルはないよ☆
		GetModuleHandle(0),						//	呼び出しアプリケーションハンドルの指定だよ☆
		nullptr									//	追加パラメータはないよ☆
	);
}

void Crown::Window::DisplayWindow()
{
	if (m_hwnd != 0)
	{
		ShowWindow(m_hwnd, SW_SHOW);					//	ウィンドウ表示するよ☆
	}
}

void Crown::Window::ProcessMessage()
{
	MSG msg;											//	ウィンドウメッセージの取得用変数だよ☆
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))	//	溜まっているウィンドウメッセージをすべて処理するよ☆
	{
		TranslateMessage(&msg);							//	ウィンドウメッセージの取得をするよ☆
		DispatchMessage(&msg);							//	ウィンドウプロージャの呼び出しだよ☆
	}
	if (msg.message == WM_QUIT)
	{
		m_endFlag = true;
	}
}

void Crown::Window::GetWindowPosition(int& x, int& y) const
{
	WINDOWINFO windowInfo;

	//ウィンドウの位置を取得するよ☆
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(m_hwnd, &windowInfo);

	x = windowInfo.rcWindow.left;
	y = windowInfo.rcWindow.top + 35;

}