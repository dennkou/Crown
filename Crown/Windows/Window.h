#pragma once
#include <iostream>
#include <Windows.h>

namespace Crown
{
	//============================================================
	// 作成日 : 2023/4/20
	// 作成者 : 服部颯澄
	// 
	// ウィンドウを管理するクラスだよ☆
	// 
	//============================================================
	class Window
	{
	public:
		Window();
		~Window();

		void MakeWindow(std::wstring windowName, WNDPROC windowProcedure, DWORD dwStyle = WS_OVERLAPPEDWINDOW);	//	ウィンドウを作成するよ☆
		void DisplayWindow();																					//	ウィンドウ表示するよ☆
		void ProcessMessage();																					//	ウィンドウメッセージを全て処理するよ☆
		inline HWND GetWindowHandle()	const { return m_hwnd; };												//	ウィンドウハンドルを返すよ☆
		inline bool GetEndFlag()		const { return m_endFlag; };											//	アプリケーションの終了フラグを返すよ☆
		void GetWindowPosition(int& x, int& y) const;
		inline int GetWindowWidth()		const { return m_width; };												//	ウィンドウの横幅を返すよ☆
		inline int GetWindowHeight()	const { return m_height; };												//	ウィンドウの高さを返すよ☆
	private:
		HWND m_hwnd;						//	ウィンドウハンドルだよ☆
		int m_width, m_height;				//	ウィンドウサイズだよ☆
		bool m_endFlag;						//	アプリケーションの終了が要求されてたかのフラグだよ☆
	};
}