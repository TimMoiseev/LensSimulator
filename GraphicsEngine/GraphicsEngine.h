#pragma once

class GraphicsEngine {
private:
	HWND hWND;
	void initOpenGL();
public :
	GraphicsEngine(HWND hWND);
	~GraphicsEngine();
	void run();

};

extern "C" __declspec(dllexport) void* createGraphicsEngine(HWND hWND);
extern "C" __declspec(dllexport) void destroyGraphicsEngine(GraphicsEngine * target);
extern "C" __declspec(dllexport) void runGraphicsEngine(GraphicsEngine * target);