#include "pch.h"
#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {

}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::run()
{

}

void* createGraphicsEngine()
{
	return new GraphicsEngine();
}

void destroyGraphicsEngine(GraphicsEngine* target)
{
	target->~GraphicsEngine();
}

void runGraphicsEngine(GraphicsEngine* target)
{
	target->run();
}