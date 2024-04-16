#pragma once
namespace Crown
{
	class Window;
	class IRenderEngine;
	class RenderEngineFactory
	{
	public:
		RenderEngineFactory() = default;
		~RenderEngineFactory() = default;

		static IRenderEngine* CreateRenderEngine(Window* renderTarget);
	private:

	};
}
