#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE  
#endif

#include <iostream>
#include <windows.h>
#include "wai/wai.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

wai* app;
void test(const POINT& pos, int options, WPARAM wParam){
    std::cout << pos.x << std::endl << pos.y << std::endl; 
    if(options == WE_LBM) std::cout << "LBM";
    else   std::cout << "RBM";
    std::cout << std::endl;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdLine){
    LPCTSTR lpClassName = L"MyAp2p";
    
    app = new wai(hInstance, lpClassName, WndProc);
    if(!app->isRegistered)
        return 3;
    CWindow* window_test = app->create<CWindow>(L"From wai", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 300, 250, 250);
    window_test->onMouseDown = test;
    
    MSG msg = {0};
    int iGetOk = 0;
    while((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0){
        if(iGetOk == -1) return 3;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;       
}
    
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){    
    return app->appProc(hWnd, message, wParam, lParam);  
}