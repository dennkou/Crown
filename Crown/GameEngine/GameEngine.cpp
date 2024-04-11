#include "GameEngine.h"

//	�V���O���g�����ɂ������L�q���恙
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

//	�N���X�{�̂��恙

Crown::GameEngine::GameEngine()
{

}

Crown::GameEngine::~GameEngine()
{

}
