#pragma once
#include <mutex>
#include "Crown.h"
#include "MultiThreadedInterface.h"

namespace Crown
{
	class GameEngine
	{
	public:
		static GameEngine& GetGameEngine();

		//	起動設定用の関数だよ☆

		//	実行☆
		void Run(std::wstring appName);

		MultiThreadedInterface<IRenderEngine>* GetRenderEngine() { return &m_renderEngine; }
	private:
		//	インナークラスの宣言☆
		class GameEngineInstance
		{
		public:
			GameEngineInstance();
			~GameEngineInstance();
			GameEngine* GetInstance();
		private:
			GameEngine* m_gameEngine;
			std::once_flag m_once;
		};

		//	ここから関数宣言☆
		GameEngine();
		~GameEngine();
		GameEngine& operator=(GameEngine& gameEngine) = delete;
		GameEngine(GameEngine& gameEngine) = delete;
		GameEngine(GameEngine&& gameEngine) = delete;
		GameEngine& operator=(GameEngine&& gameEngine) = delete;

		static LRESULT CrownWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		//	ここから変数宣言☆
		static GameEngineInstance instance;
		std::mutex m_mutex;
		Window m_mainWindow;
		MultiThreadedInterface<IRenderEngine> m_renderEngine;		
	};
}