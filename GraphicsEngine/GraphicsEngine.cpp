#include "pch.h"
#include "GraphicsEngine.h"
#include <chrono>
#include "ShaderProgramManager.h"
#include "ShaderSystem.h"
#include "Cube.h"
#include "BiconvexLens.h"
#include "Line.h"
#include "Grid.h"

void GraphicsEngine::beginMainLoop()
{
    vec3 red = vec3(255.0f, 0.0f, 0.0f);
    vec3 green = vec3(0.0f, 255.0f, 0.0f);
    vec3 blue = vec3(0.0f, 0.0f, 255.0f);

    BiconvexLens lens;
    Line axisX(vec3(0, 0, 0), vec3(100, 0, 0), red);
    Line axisY(vec3(0, 0, 0), vec3(0, 100, 0), green);
    Line axisZ(vec3(0, 0, 0), vec3(0, 0, 100), blue);
    Grid grid(20, 20);

    auto lastTime = std::chrono::high_resolution_clock::now();

	while (true) {

        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if ((messageSystem->getCurrentMessage())["Type"].template get<std::string>() == "Resize") {
            glViewport(0, 0, 
                messageSystem->getCurrentMessage()["Width"].template get<UINT>(),
                messageSystem->getCurrentMessage()["Height"].template get<UINT>());
        }
        renderer.draw(&lens);
        
        camera.update((float)duration);
        renderer.setCamera(&camera);
        renderer.draw(&grid);
        renderer.draw(&axisX);
        renderer.draw(&axisY);
        renderer.draw(&axisZ);
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