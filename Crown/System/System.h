#pragma once
#include "Crown.h"

//	OSに依存する部分を抜き出したクラスだよ☆
class Crown<class t>::System
{
public:
	System(std::string AppName) {};
	virtual ~System() {};

	virtual void CreateRenderSystem() = 0;
private:
};