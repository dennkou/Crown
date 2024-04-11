#pragma once
#include <mutex>

namespace Crown
{
	//	���C�u�����{�̂��恙�}���`�X���b�h�ɑΉ����Ă���恙
	class GameEngine
	{
	//	�V���O���g�����ɂ������L�q���恙
	public:
		static GameEngine& GetGameEngine();
	private:
		GameEngine();
		~GameEngine();
		GameEngine& operator=(GameEngine& gameEngine) = delete;
		GameEngine(GameEngine& gameEngine) = delete;
		GameEngine(GameEngine&& gameEngine) = delete;
		GameEngine& operator=(GameEngine&& gameEngine) = delete;
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
		static GameEngineInstance instance;

	//	�}���`�X���b�h���̂��߂̋L�q���恙
	public:
	private:
		std::mutex m_mutex;

	//	���C�u�����̊Ǘ��ׂ̈̋L�q���恙
	public:
	private:

	};
}