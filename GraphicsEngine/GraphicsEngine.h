#pragma once
#include "GL/glew.h"
#include "GL/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "WindowSystem.h"
#include "Renderer.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include <sstream>
#include "Scene.h"
#include "Camera.h"
#include "ShaderProgramManager.h"
#include "MessageProcessingSystem.h"
#include "HIDInputSystem.h"
#pragma comment(lib, "glew32.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glfw3dll.lib")

class GraphicsEngine {
private:
	HWND hWND;
	HDC dc;
	const char* vertFilePath = "C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\GraphicsEngine\\Shader\\shader.vert";
	const char* fragFilePath = "C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\GraphicsEngine\\Shader\\shader.frag";
	WindowSystem windowSystem{ hWND, dc };
	Shader vertexShader = Shader(vertFilePath, GL_VERTEX_SHADER);
	Shader fragShader = Shader(fragFilePath, GL_FRAGMENT_SHADER);
	std::vector<Shader*> shaders{&vertexShader, &fragShader};
	ShaderProgramManager shaderProgram{&shaders};
	ShaderSystem shaderSystem{&shaderProgram};
	MessageProcessingSystem* messageSystem = MessageProcessingSystem::create();
	Camera camera{ vec3(200.0, 200.0, 200.0) };
	HIDInputSystem inputSystem{ messageSystem };
	Renderer renderer{&shaderSystem};
	std::vector<OpticElement*> lensSystem = {};
	void resizeCallback(int width, int height);
	bool stopped = false;
	void beginMainLoop();
	int X = 0;
	int Y = 0;
	

public :
	
	/*void draw(GraphicsObject obj);*/
	GraphicsEngine(HWND hWND);
	~GraphicsEngine();
	void run();
	void stop();
};

extern "C" __declspec(dllexport) void* createGraphicsEngine(HWND hWND);
extern "C" __declspec(dllexport) void destroyGraphicsEngine(GraphicsEngine * target);
extern "C" __declspec(dllexport) void runGraphicsEngine(GraphicsEngine * target);