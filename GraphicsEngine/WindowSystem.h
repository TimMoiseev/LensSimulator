#pragma once
class WindowSystem
{
private:
	HWND hWnd;
	HDC dc;
	void createGLContext();
	HGLRC renderContext;
public:
	WindowSystem();
	
	WindowSystem(HWND hWND, HDC dc);
};

