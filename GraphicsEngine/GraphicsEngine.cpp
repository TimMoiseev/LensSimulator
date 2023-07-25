#include "pch.h"
#include "GraphicsEngine.h"



void GraphicsEngine::initOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // �����
		PFD_TYPE_RGBA,        // ���-�� ����� �����������. RGBA ��� �������.
		32,                   // �������� ������� �����������.
		0, 0, 0, 0, 0, 0,
		24,
		0,
		0,
		0, 0, 0, 0,
		24,                    // ���������� ����� ��� ������ �������
		8,                    // ���������� ����� ��� ������ ���������
		0,                    // ���������� ��������������� ������� � ������ ������.
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