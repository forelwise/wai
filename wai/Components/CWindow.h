#include <windows.h>
#include "CObject.h"
#ifndef _WAPI_CWindow
#define _WAPI_CWindow
class CWindow : public CObject{
    public:
        CWindow(LPCTSTR, LPCTSTR, DWORD, int, int, int, int, HINSTANCE, HWND);
        LRESULT customProc(UINT, WPARAM, LPARAM);
        //TODO перенести базовые собития и обработчик в CObject как виртуальный? 

        //Нажатие/отпускание мышки
        //POINT - координаты, int - WE_LBM/RBM/MBM, WPARAM - доп.параметры 
        void (*onMouseDown)(const POINT&, int, WPARAM) = nullptr; 
        void (*onMouseUp)(const POINT&, int, WPARAM) = nullptr;
        //Разрушение обьекта
        void (*onDestroy)() = nullptr; 
};
LRESULT CWindow::customProc(UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_LBUTTONDOWN:
            if(onMouseDown != nullptr) 
                onMouseDown(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_LBM, wParam);
        break;
        case WM_LBUTTONUP:
            if(onMouseUp != nullptr) 
                onMouseUp(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_LBM, wParam);
        break;
        case WM_RBUTTONDOWN:
            if(this->onMouseDown != nullptr) 
                this->onMouseDown(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_RBM, wParam);
        break;
        case WM_RBUTTONUP:
            if(this->onMouseUp != nullptr) 
                this->onMouseUp(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_RBM, wParam);
        break;
        case WM_MBUTTONDOWN:
            if(this->onMouseDown != nullptr) 
                this->onMouseDown(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_MBM, wParam);
        break;
        case WM_MBUTTONUP:
            if(this->onMouseUp != nullptr) 
                this->onMouseUp(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_MBM, wParam);
        break;
        case WM_DESTROY:
            if(this->onDestroy != nullptr)
                this->onDestroy();
        break;
        default:    
            return DefWindowProc(this->getHWND(), msg, wParam, lParam);
    }
    return 0;
}

/**
 * @brief Конструктор нового обьекта CWindow::CWindow 
 * 
 * @param lpDefinedText заголовок окна
 * @param lpClassName имя класса приложения
 * @param dwStyle стиль окна
 * @param x позиция Х
 * @param y позиция Y
 * @param width ширина окна
 * @param height высота окна
 * @param hInst дескриптор приложения
 * @param hWndParent дескриптор родительского окна 
 */
CWindow::CWindow(LPCTSTR lpDefinedText, LPCTSTR lpClassName, DWORD dwStyle, int x, int y, int width, int height, HINSTANCE hInst, HWND hWndParent = NULL) : CObject(lpClassName, dwStyle, hInst){
    this->_hWnd = CreateWindow(lpClassName, lpDefinedText, dwStyle, x, y, width, height, hWndParent, NULL, hInst, NULL);
}
#endif