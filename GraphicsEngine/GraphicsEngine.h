#pragma once

class GraphicsEngine {
public :
	GraphicsEngine();
	~GraphicsEngine();
	void run();
};

extern "C" __declspec(dllexport) void* createGraphicsEngine();
extern "C" __declspec(dllexport) void destroyGraphicsEngine(GraphicsEngine * target);
extern "C" __declspec(dllexport) void runGraphicsEngine(GraphicsEngine * target);