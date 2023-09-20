#pragma once
#include <wtypes.h>
class WindowSystem
{
private:
	HWND hWnd;
	HDC dc;
	void createGLContext();
	HGLRC renderContext;
public:
	WindowSystem(HWND hWND, HDC dc);
};

