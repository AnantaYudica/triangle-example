#include <windows.h>

#ifdef USING_DIRECT3D
#include "graphics/Direct3d.h"
#elif USING_OPENGL
#include "graphics/Wgl.h"
#include <gl/GL.h>
#endif
#include "Triangle.h"

#include <memory>

std::shared_ptr<Triangle> triangle{ nullptr };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Triangle",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

#ifdef USING_DIRECT3D
    graphics::Direct3d::GetInstance().Init(hwnd);
#elif USING_OPENGL
    graphics::Wgl::GetInstance().Init(hwnd);

    MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
#endif 

#ifdef USING_DIRECT3D
    triangle = std::make_shared<Triangle>(&graphics::Direct3d::GetInstance());
    triangle->Init();
#elif USING_OPENGL
#endif 

    ShowWindow(hwnd, nCmdShow);
    
    MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

#ifdef USING_DIRECT3D
        graphics::Direct3d::GetInstance().BeginDraw();
#elif USING_OPENGL
#endif 
        triangle->Draw();
#ifdef USING_DIRECT3D
        graphics::Direct3d::GetInstance().EndDraw();
#elif USING_OPENGL
#endif 
    }

    return (int)msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            if (triangle) triangle.reset();
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
