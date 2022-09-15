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

void test_click(){
    std::cout << "hello click" << std::endl;    
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdLine){
    LPCTSTR lpClassName = L"MyAp2p";
    
    app = new wai(hInstance, lpClassName, WndProc);
    if(!app->isRegistered)
        return 3;
    CWindow* window_test = app->create<CWindow>(L"From wai", WS_OVERLAPPEDWINDOW | WS_VISIBLE, POINT({150, 150}), SIZE({400, 400}));
    CButton* button1 = window_test->create<CButton>(L"Test", POINT({0, 0}), SIZE({200, 150}));   
    button1->onClick = test_click;

    window_test->onDestroy = [](){
        PostQuitMessage(0);
    };
    
    
    
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