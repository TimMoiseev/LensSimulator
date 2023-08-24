#include "pch.h"
#include "GraphicsEngine.h"
#include <chrono>
#include "ShaderProgramManager.h"
#include "ShaderSystem.h"
#include "Cube.h"
#include "BiconvexLens.h"

void GraphicsEngine::beginMainLoop()
{
    
    
    Cube cube2{5.5f, 1.0f, 10.0f, 0.2f};
    BiconvexLens lens;
    auto lastTime = std::chrono::high_resolution_clock::now();
    renderer.setCamera(&camera);

	while (true) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        cube2.update((float)duration);
        glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        renderer.draw(&cube2);
        renderer.draw(&lens);
        camera.update((float)duration);
        renderer.setCamera(&camera);
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
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