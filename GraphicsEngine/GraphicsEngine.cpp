#include "pch.h"
#include "GraphicsEngine.h"
#include "GL/glew.h"
#include "GL/gl.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")



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
	auto pf = ChoosePixelFormat(GetDC(hWND), &pfd);
}

GraphicsEngine::GraphicsEngine(HWND hWND) : hWND{ hWND } {

}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::run()
{
	initOpenGL();
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