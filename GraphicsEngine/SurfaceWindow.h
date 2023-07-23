#pragma once

#include "Windows.h"

extern "C" __declspec(dllexport) bool registerSurfaceWindowClassExport();

extern "C" __declspec(dllexport) HWND createSurfaceWindowExport(HWND hwndParrent);

//extern "C" __declspec(dllexport) LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

extern "C" __declspec(dllexport) void showSurfaceWindowExport(HWND hwnd);

bool registerSurfaceWindowClass(HINSTANCE hInstance, const wchar_t* strClassName, WNDPROC pfnWindowProcedure);
bool registerSurfaceWindowClassExport();

HWND createSurfaceWindow(HINSTANCE wInstance, HWND hwndParrent);
HWND createSurfaceWindowExport(HWND hwndParrent);

//void startWndLoop(HWND hWnd);

void showSurfaceWindowExport(HWND hwnd);
void showSurfaceWindow(HWND hwnd);

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);