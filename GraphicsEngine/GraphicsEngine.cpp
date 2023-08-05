#include "pch.h"
#include "GraphicsEngine.h"
#include "GraphicsObject.h"
#include <chrono>
#include "ShaderProgramManager.h"
#include "ShaderSystem.h"

void GraphicsEngine::beginMainLoop()
{
    std::vector<Vertex> v{
            Vertex({ 0.125f,  0.125f,  0.125f }, { 1.0, 0.0, 0.0 }),
            Vertex({ -0.125,  -0.125f,  0.125f }, { 0.0, 1.0, 0.0 }),
            Vertex({ 0.125f,  -0.125f,  0.125f }, { 0.0, 0.0, 1.0 }),

            Vertex({ 0.125f,  -0.125f,  -0.125f }, { 1.0, 0.0, 0.0 }),
            Vertex({ -0.125,  0.125f,  -0.125f }, { 0.0, 1.0, 0.0 }),
            Vertex({ 0.125f,  0.125f,  -0.525f }, { 0.0, 0.0, 1.0 })
            
    };
    
    std::vector<Vertex> v2{
            Vertex({ -0.825f,  0.825f,  0.125f }, { 0.0, 1.0, 1.0 }),
            Vertex({ -0.825f,  -0.825f,  0.125f }, { 0.0, 1.0, 0.0 }),
            Vertex({ 0.125f,  -0.125f,  -0.125f }, { 0.0, 0.0, 1.0 }),

            Vertex({ 0.125f,  -0.825f,  -0.125f }, { 0.0, 1.0, 0.0 }),
            Vertex({ 0.825f,  0.825f,  -0.825f }, { 0.0, 1.0, 0.0 }),
            Vertex({ 0.825f,  0.125f,  -0.125f }, { 0.0, 0.0, 1.0 })

    };
    
    
    
    
    Scene scene(v, Coordinate | Color);
    Scene scene2(v2, Coordinate | Color);
    std::vector<std::string> uniformParameterNames;
    uniformParameterNames.push_back("cameraMatrix");
    uniformParameterNames.push_back("objectMatrix");
    std::vector<GLfloat*> uniformParameterPointers;
    uniformParameterPointers.push_back(&camera.getCameraMatrix()[0][0]);
    uniformParameterPointers.push_back(&scene.objectMatrix[0][0]);
    uniformParameterPointers.push_back(&scene2.objectMatrix[0][0]);
    ShaderSystem shaderSystem = ShaderSystem(&shaderProgram, uniformParameterNames, uniformParameterPointers);
    const VertexBuffer& vbuf = scene.VerticesView();
    const VertexBuffer& vbuf2 = scene2.VerticesView();
    auto lastTime = std::chrono::high_resolution_clock::now();
    GraphicsObject objects;
    objects.add(&scene);
    objects.add(&scene2);

	while (true) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        objects.update(duration);
        shaderProgram.use();
        
        shaderSystem.bindUniformParameters("cameraMatrix");
        glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.bindArrayAtrib();
        shaderSystem.bindUniformParameters("objectMatrix");
        renderer.bindVertexBuffer(vbuf);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        scene2.bindArrayAtrib();
        renderer.bindVertexBuffer(vbuf2);
        
        
        
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