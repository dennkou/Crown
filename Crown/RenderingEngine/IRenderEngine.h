#pragma once

namespace Crown
{
	class IModel;
	class IRenderEngine
	{
	public:
		IRenderEngine() {};
		virtual ~IRenderEngine() {};

		virtual void Render() = 0;
	private:

	};
}