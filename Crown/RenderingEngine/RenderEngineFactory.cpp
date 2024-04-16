#include "RenderEngineFactory.h"
#include "RenderEngine.h"
Crown::IRenderEngine* Crown::RenderEngineFactory::CreateRenderEngine(Window* renderTarget)
{
	return new RenderEngine(renderTarget);
}
