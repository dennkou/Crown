#pragma once
#include "Crown.h"

//	OS�Ɉˑ����镔���𔲂��o�����N���X���恙
class Crown<class t>::System
{
public:
	System(std::string AppName) {};
	virtual ~System() {};

	virtual void CreateRenderSystem() = 0;
private:
};