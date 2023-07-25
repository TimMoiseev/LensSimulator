#pragma once
#include "GL/glew.h"
#include "GL/gl.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
class GraphicsEngine {
private:
	HWND hWND;
	HDC dc;
	HGLRC renderContext;
	void initOpenGL();
	void beginMainLoop();
public :
	GraphicsEngine(HWND hWND);
	~GraphicsEngine();
	void run();

};

extern "C" __declspec(dllexport) void* createGraphicsEngine(HWND hWND);
extern "C" __declspec(dllexport) void destroyGraphicsEngine(GraphicsEngine * target);
extern "C" __declspec(dllexport) void runGraphicsEngine(GraphicsEngine * target);