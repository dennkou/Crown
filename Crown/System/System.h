#pragma once
#include "Crown.h"

//	OSに依存する部分を抜き出したクラスだよ☆
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