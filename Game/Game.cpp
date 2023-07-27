#include "Game.h"
#include "./../Crown/Object/Input.h"
#include "./../Crown/Object/RenderSystem/Camera.h"

Game::Game()
{
	m_model.SetPosition(DirectX::XMFLOAT3(0.0f,0.0f,0.0f));
	m_model.LoadPMD(L"Resource/Model/PMD/‰‰¹ƒ~ƒN.pmd");
}

Game::~Game()
{

}

void Game::Updata()
{
	float angle = 0;

	angle = Crown::Input::GetMouse()->GetMousePosint().x / 100;

	DirectX::XMFLOAT3 eye(sin(angle) * 20, 10, cos(angle) * 20);
	DirectX::XMFLOAT3 target(0, 10, 0);
	DirectX::XMFLOAT3 up(0, 1, 0);
	Crown::RenderObject::Camera::GetInstance()->SetView(DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up)));
}