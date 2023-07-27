#include "pch.h"
#include "WindowSystem.h"
#include <GL/glew.h>

void WindowSystem::createGLContext()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		24,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	glewExperimental = TRUE;
	if (auto pf = ChoosePixelFormat(dc, &pfd)) {
		if (SetPixelFormat(dc, pf, &pfd)) {
			renderContext = wglCreateContext(dc);

			if (wglMakeCurrent(dc, renderContext)) {
				if (glewInit() == GLEW_OK) {
					int a = 5;
				}
			}
		}
	}
}



WindowSystem::WindowSystem(HWND hWND, HDC dc) : hWnd{hWND}, dc{ dc }
{
	createGLContext();
}
