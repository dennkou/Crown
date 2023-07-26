#include "Game.h"

Game::Game()
{
	m_model.SetPosition(DirectX::XMFLOAT3(0.0f,0.0f,0.0f));
	m_model.LoadPMD(L"Resource/Model/PMD/èââπÉ~ÉN.pmd");
}

Game::~Game()
{
}

void Game::Updata()
{

}