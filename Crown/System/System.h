#pragma once
#include "Crown.h"

//	OS�Ɉˑ����镔���𔲂��o�����N���X���恙
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