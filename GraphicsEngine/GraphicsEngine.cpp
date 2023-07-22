#include "pch.h"
#include "GraphicsEngine.h"

GraphicEngine::GraphicEngine() {

}

void GraphicEngine::run()
{

}

void* createGraphicsEngine()
{
	return new GraphicEngine();
}

void destroyGraphicsEngine(GraphicEngine* target)
{
	target->~GraphicEngine();
}

void runGraphicsEngine(GraphicEngine* target)
{
	return target->run();
}