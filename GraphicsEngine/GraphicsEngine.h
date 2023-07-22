#pragma once

class GraphicEngine {
public :
	GraphicEngine();
	void run();
};

extern "C" __declspec(dllexport) void* createGraphicsEngine();
extern "C" __declspec(dllexport) void destroyGraphicsEngine(GraphicEngine * target);
extern "C" __declspec(dllexport) void runGraphicsEngine(GraphicEngine * target);