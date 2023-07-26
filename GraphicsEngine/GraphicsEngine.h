#pragma once
#include "GL/glew.h"

#include "GL/gl.h"

#include "glm/glm.hpp"
#pragma comment(lib, "glew32.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glfw3dll.lib")



class GraphicsEngine {
private:
	HWND hWND;
	HDC dc;
	HGLRC renderContext;
	void initOpenGL();
	void beginMainLoop();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
public :
	GraphicsEngine(HWND hWND);
	~GraphicsEngine();
	void run();

};

extern "C" __declspec(dllexport) void* createGraphicsEngine(HWND hWND);
extern "C" __declspec(dllexport) void destroyGraphicsEngine(GraphicsEngine * target);
extern "C" __declspec(dllexport) void runGraphicsEngine(GraphicsEngine * target);