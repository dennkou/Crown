#include "System.h"
#include "Object/Input.h"
#include <Windows.h>



Crown::System* Crown::System::m_system = nullptr;



Crown::System::System()
	:
	m_endFlag(false)
{
}

Crown::System::~System()
{
}

Crown::System* Crown::System::GetInstance()
{
	if (m_system == nullptr)
	{
		m_system = new System();
	}
	return m_system;
}

LRESULT CrownWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void Crown::System::Initialize()
{
	m_window.MakeWindow(L"Crown", CrownWindowProcedure, WS_OVERLAPPEDWINDOW);
	m_window.DisplayWindow();
}

void Crown::System::Update()
{
	m_window.ProcessMessage();
	m_endFlag = m_window.GetEndFlag();
}

void Crown::System::Finalize()
{

}



LRESULT CrownWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_DESTROY:		//ウィンドウが破棄された☆
			PostQuitMessage(0);	//アプリケーションの終了☆
			break;

		//	入力系だよ☆
		//case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			Crown::Input::GetKeyboardMessage()->DownMessage(wparam);
			break;
		//case WM_SYSKEYUP:
		case WM_KEYUP:
			Crown::Input::GetKeyboardMessage()->UpMessage(wparam);
			break;
		case WM_LBUTTONDOWN:
			Crown::Input::GetMouseMessage()->LButtonDownMessage();
			break;
		case WM_LBUTTONUP:
			Crown::Input::GetMouseMessage()->LButtonUpMessage();
			break;
		case WM_MBUTTONDOWN:
			Crown::Input::GetMouseMessage()->MButtonDownMessage();
			break;
		case WM_MBUTTONUP:
			Crown::Input::GetMouseMessage()->MButtonUpMessage();
			break;
		case WM_RBUTTONDOWN:
			Crown::Input::GetMouseMessage()->RButtonDownMessage();
			break;
		case WM_RBUTTONUP:
			Crown::Input::GetMouseMessage()->RButtonUpMessage();
			break;
		case WM_MOUSEMOVE:
			Crown::Input::GetMouseMessage()->MoveMessage(lparam);
			break;
		case WM_MOUSEWHEEL:
			Crown::Input::GetMouseMessage()->WheelMessage(wparam);
			break;
		default:
			break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}