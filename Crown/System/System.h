#pragma once
#include "Crown.h"

//	OS‚ÉˆË‘¶‚·‚é•”•ª‚ğ”²‚«o‚µ‚½ƒNƒ‰ƒX‚¾‚æ™
class Crown<class t>::System
{
public:
	System(std::string AppName) {};
	virtual ~System() {};

	virtual void CreateRenderSystem() = 0;
private:
};