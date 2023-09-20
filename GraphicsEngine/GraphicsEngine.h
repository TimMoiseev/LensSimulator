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
	Camera camera{ vec3(200.0, 200.0, 200.0) };
	Renderer renderer{&shaderSystem};
	MessageProcessingSystem* messageSystem = MessageProcessingSystem::create();
	bool stopped = false;
	void beginMainLoop();
	
	

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