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

    HWND hSwitch = CreateWindowExA(
        0,
        "BUTTON",
        "Enable This Feature",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        200, 200,
        100, 100,
        hWnd,
        (HMENU)1002,
        hInstance,
        NULL
    );

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
        case WM_COMMAND : {
            if (LOWORD(wParam) == 1002) {
                LRESULT checked = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);

                if (checked == BST_CHECKED)
                    MessageBoxA(NULL, "Feature Enabled.", "Information", MB_ICONINFORMATION);
                else
                    MessageBoxA(NULL, "Feature Disabled.", "Information", MB_ICONINFORMATION);
            }
        }
        
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}