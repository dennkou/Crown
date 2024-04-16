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

		//	�N���ݒ�p�̊֐����恙

		//	���s��
		void Run(std::wstring appName);

		MultiThreadedInterface<IRenderEngine>* GetRenderEngine() { return &m_renderEngine; }
	private:
		//	�C���i�[�N���X�̐錾��
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

		//	��������֐��錾��
		GameEngine();
		~GameEngine();
		GameEngine& operator=(GameEngine& gameEngine) = delete;
		GameEngine(GameEngine& gameEngine) = delete;
		GameEngine(GameEngine&& gameEngine) = delete;
		GameEngine& operator=(GameEngine&& gameEngine) = delete;

		static LRESULT CrownWindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		//	��������ϐ��錾��
		static GameEngineInstance instance;
		std::mutex m_mutex;
		Window m_mainWindow;
		MultiThreadedInterface<IRenderEngine> m_renderEngine;		
	};
}