#include "pch.h"
#include "SurfaceWindow.h"

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    json message = {
        {"Type", "Resize"},
        {"Priority", 0.8f},
        {"Width", LOWORD(lParam)},
        {"Height", HIWORD(lParam)},
    };
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        MessageProcessingSystem::create()->reciveMessage(message);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

HWND createSurfaceWindow(HINSTANCE wInstance, HWND hwndParrent) {
    auto g_hwnd = CreateWindowEx(
        CS_HREDRAW | CS_VREDRAW,
        L"AppWindowClass",
        L"OpenGL Surface child window",
        WS_CHILD,
        0, 0,
        1920, 1080,
        hwndParrent,
        nullptr,
        wInstance,
        nullptr);
    auto result = GetLastError();
    return g_hwnd;
}

bool registerSurfaceWindowClass(HINSTANCE hInstance, const wchar_t* strClassName, WNDPROC pfnWindowProcedure) {
    
    WNDCLASSEX classInfo = {};
    classInfo.cbSize = sizeof(WNDCLASSEX);
    classInfo.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    classInfo.cbClsExtra = 0;
    classInfo.cbWndExtra = 0;
    classInfo.hInstance = hInstance;
    classInfo.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    classInfo.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
    classInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
    classInfo.hbrBackground = CreateSolidBrush(RGB(128, 128, 240));
    classInfo.lpszMenuName = nullptr;
    classInfo.lpszClassName = strClassName;
    classInfo.lpfnWndProc = pfnWindowProcedure;
    return RegisterClassEx(&classInfo) != 0;;
}

void showSurfaceWindow(HWND hwnd) {
    ShowWindow(hwnd, SW_SHOWNORMAL);
}

void destroyWindow(HWND hwnd) {
    DestroyWindow(hwnd);
}

void destroyWindowExport(HWND hwnd) {
    destroyWindow(hwnd);
}

HWND createSurfaceWindowExport(HWND hwndParrent) {
    HWND handle = createSurfaceWindow(GetModuleHandle(nullptr), hwndParrent);
    return handle;
}

void showSurfaceWindowExport(HWND hwnd) {
    showSurfaceWindow(hwnd);
}

bool registerSurfaceWindowClassExport() {
    return registerSurfaceWindowClass(GetModuleHandle(nullptr), L"AppWindowClass", WindowProcedure);
}