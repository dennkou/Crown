#include "GameEngine.h"

//	シングルトン化にかかわる記述だよ☆
Crown::GameEngine::GameEngineInstance::GameEngineInstance()
	:
	m_gameEngine(nullptr)
{

}

Crown::GameEngine::GameEngineInstance::~GameEngineInstance()
{
	if (m_gameEngine)
	{
		delete m_gameEngine;
	}
}

Crown::GameEngine* Crown::GameEngine::GameEngineInstance::GetInstance()
{
	std::call_once
	(m_once, [&]
		{
			if (!m_gameEngine)
			{
				m_gameEngine = new GameEngine();
			}
		}
	);
	return m_gameEngine;
}

Crown::GameEngine::GameEngineInstance Crown::GameEngine::instance;
Crown::GameEngine& Crown::GameEngine::GetGameEngine()
{
	return *instance.GetInstance();
}

//	クラス本体だよ☆

Crown::GameEngine::GameEngine()
{
}

Crown::GameEngine::~GameEngine()
{
}

void Crown::GameEngine::Run(std::wstring appName)
{
	m_mainWindow.MakeWindow(appName, CrownWindowProcedure);
	m_mainWindow.DisplayWindow();
	m_renderEngine.Reset(RenderEngineFactory::CreateRenderEngine(&m_mainWindow));

	while(!m_mainWindow.GetEndFlag())
	{
		m_mainWindow.ProcessMessage();
		m_renderEngine.CallFunction(&IRenderEngine::Render);
	}
}


LRESULT Crown::GameEngine::CrownWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:		//ウィンドウが破棄された☆
		PostQuitMessage(0);	//アプリケーションの終了☆
		break;

		//	入力系だよ☆
		//case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		break;
		//case WM_SYSKEYUP:
	case WM_KEYUP:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MBUTTONDOWN:
		break;
	case WM_MBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_MOUSEWHEEL:
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
