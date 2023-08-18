#include "pch.h"
#include "GraphicsEngine.h"
#include <chrono>
#include "ShaderProgramManager.h"
#include "ShaderSystem.h"
#include "Cube.h"

void GraphicsEngine::beginMainLoop()
{
    
    Cube cube;
    Cube cube2{1.1f};
    //std::vector<std::string> uniformParameterNames;
    //uniformParameterNames.push_back("cameraMatrix");
    //uniformParameterNames.push_back("objectMatrix");
    //std::vector<GLfloat*> uniformParameterPointers;
    //uniformParameterPointers.push_back(&camera.getCameraMatrix()[0][0]);
    //uniformParameterPointers.push_back(&cube.objectMatrix[0][0]);
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    renderer.setCamera(&camera);

	while (true) {
        
        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        cube.update((float)duration);
        cube2.update(2.0*(float)duration);
        glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        renderer.draw(&cube);
        renderer.draw(&cube2);
        /*shaderSystem.bindUniformParameters("cameraMatrix");
        glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.bindArrayAttrib();
        shaderSystem.bindUniformParameters("objectMatrix");
        renderer.bindVertexBuffer(cube.VerticesView());
        glDrawArrays(GL_TRIANGLES, 0, 6*3);*/
		SwapBuffers(dc);
       
	}
}
void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

GraphicsEngine::GraphicsEngine(HWND hWND) : hWND{ hWND }, dc{ GetDC(hWND) } {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
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