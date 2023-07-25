#include "pch.h"
#include "GraphicsEngine.h"



void GraphicsEngine::initOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Ôëàãè
		PFD_TYPE_RGBA,        // ×òî-òî âğîäå ôğåéìáóôåğà. RGBA èëè ïàëèòğà.
		32,                   // Öâåòîâàÿ ãëóáèíà ôğåéìáóôåğà.
		0, 0, 0, 0, 0, 0,
		24,
		0,
		0,
		0, 0, 0, 0,
		24,                    // Êîëè÷åñòâî áèòîâ äëÿ áóôåğà ãëóáèíû
		8,                    // Êîëè÷åñòâî áèòîâ äëÿ áóôåğà òğàôàğåòà
		0,                    // Êîëè÷åñòâî âñïîìîãàòåëüíûõ áóôåğîâ â áóôåğå êàäğîâ.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	
	if (auto pf = ChoosePixelFormat(dc, &pfd)) {
		if (SetPixelFormat(dc, pf, &pfd)) {
			renderContext = wglCreateContext(dc);
			bool result = wglMakeCurrent(dc, renderContext);
		}
	}
	
	
	
}

void GraphicsEngine::beginMainLoop()
{
	while (true) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(dc);
	}
}

GraphicsEngine::GraphicsEngine(HWND hWND) : hWND{ hWND }, dc{ GetDC(hWND) } {

}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::run()
{
	initOpenGL();
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