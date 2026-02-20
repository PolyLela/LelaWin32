#include <windows.h>
#include <iostream>

constexpr char className[] = "LelaWin32";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    WNDCLASSA wc{};
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = className;

    if (!RegisterClassA(&wc)) {
        MessageBoxA(NULL, "Failed To Register Window Class.", "Error", MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowExA(
        WS_EX_OVERLAPPEDWINDOW,
        className,
        "LelaWin",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 400,
        nullptr,
        nullptr,
        hInstance,
        0
    );

    if (!hWnd) {
        MessageBoxA(NULL, "Failed To Create Window For This Instance.", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_DESTROY : {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}