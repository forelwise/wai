#include <windows.h>
#include "CObject.h"
#ifndef _WAPI_CWindow
#define _WAPI_CWindow
class CWindow : public CObject{
    public:
        CWindow(LPCTSTR, LPCTSTR, DWORD, int, int, int, int, HINSTANCE, HWND);
        void objectProc(UINT, WPARAM, LPARAM);
        //TODO перенести базовые собития и обработчик в CObject как виртуальный? 
};
void CWindow::objectProc(UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        
    }
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