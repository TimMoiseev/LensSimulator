#include "pch.h"
#include "GraphicsEngine.h"
#include <chrono>
#include "ShaderProgramManager.h"
#include "ShaderSystem.h"
#include "Cube.h"

void GraphicsEngine::beginMainLoop()
{
    Cube cube;
    
    std::vector<std::string> uniformParameterNames;
    uniformParameterNames.push_back("cameraMatrix");
    uniformParameterNames.push_back("objectMatrix");
    std::vector<GLfloat*> uniformParameterPointers;
    uniformParameterPointers.push_back(&camera.getCameraMatrix()[0][0]);
    uniformParameterPointers.push_back(&cube.objectMatrix[0][0]);
    ShaderSystem shaderSystem = ShaderSystem(&shaderProgram, uniformParameterNames, uniformParameterPointers);
  
    auto lastTime = std::chrono::high_resolution_clock::now();


	while (true) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        cube.update((float)duration);
        shaderProgram.use();
        
        shaderSystem.bindUniformParameters("cameraMatrix");
        glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.bindArrayAttrib();
        shaderSystem.bindUniformParameters("objectMatrix");
        renderer.bindVertexBuffer(cube.VerticesView());
        glDrawArrays(GL_TRIANGLES, 0, 6);
		SwapBuffers(dc);
	}
}


GraphicsEngine::GraphicsEngine(HWND hWND) : hWND{ hWND }, dc{ GetDC(hWND) } {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::run()
{
    beginMainLoop();
}

void* createGraphicsEngine(HWND hWND)
{
	return new GraphicsEngine(hWND);
}

void destroyGraphicsEngine(GraphicsEngine* target)
{
	target->~GraphicsEngine();
}

void runGraphicsEngine(GraphicsEngine* target)
{
	target->run();
}