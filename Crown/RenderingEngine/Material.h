#pragma once
#include "Resource.h"
#include "Vertices.h"

namespace Crown
{
	class Material
	{
	public:
		Material();
		~Material();


	private:
		//std::vector<Resource> m_resource;
		unsigned int m_descriptorOffset;
	};
}