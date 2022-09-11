#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE  
#endif
#include <iostream>
#include <windows.h>
#include "wai/wai.h"

ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdLine){
    LPCTSTR lpClassName = L"MyAp2p";
    
    wai test(hInstance, lpClassName, WndProc);
    if(!test.isRegistered)
        return 3;

    HWND hWnd = CreateWindow(lpClassName, L"TEST", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 200, 200, NULL, NULL, hInstance, NULL);
    if(!hWnd)
        return 2;
    MSG msg = {0};
    int iGetOk = 0;
    while((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0){
        if(iGetOk == -1) return 3;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    /*

        CWindow window1 = app.newWindow(params);
        window1.show();

        CButton c = window1.new<CButton>(paraams);
        c.text(...);
        c.position...
        

    */
    return msg.wParam;       
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){            
    switch (message)
    {
    case WM_LBUTTONUP:
        MessageBox(hWnd, L"Привет", L"собыите", 0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}