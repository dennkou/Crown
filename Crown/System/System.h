#pragma once
#include "Crown.h"

//	OS‚ÉˆË‘¶‚·‚é•”•ª‚ğ”²‚«o‚µ‚½ƒNƒ‰ƒX‚¾‚æ™
namespace Crown
{
	class System
	{
	public:
		System() {};
		virtual ~System() {};

		virtual void CreateRenderSystem() = 0;
	private:
	};
}