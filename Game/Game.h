#pragma once
#include "./Player.h"

class Game
{
public:
	Game();
	~Game();

	void Updata();
private:
	Player m_player;
};