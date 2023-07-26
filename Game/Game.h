#pragma once
#include "./../Crown/Object/RenderSystem/Model/Model.h"
class Game
{
public:
	Game();
	~Game();

	void Updata();
private:
	Crown::RenderObject::Model m_model;
};