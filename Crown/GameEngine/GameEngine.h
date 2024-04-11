#pragma once
#include <mutex>

namespace Crown
{
	//	ライブラリ本体だよ☆マルチスレッドに対応しているよ☆
	class GameEngine
	{
	//	シングルトン化にかかわる記述だよ☆
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

	//	マルチスレッド化のための記述だよ☆
	public:
	private:
		std::mutex m_mutex;

	//	ライブラリの管理の為の記述だよ☆
	public:
	private:

	};
}