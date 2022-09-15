#include <windows.h>
#include "CObject.h"
#ifndef _WAPI_CWindow
#define _WAPI_CWindow
class CWindow : public CObject{
    public:
        CWindow(LPCTSTR, LPCTSTR, DWORD, const POINT&, const SIZE&, HINSTANCE, HWND);
        LRESULT customProc(UINT, WPARAM, LPARAM);
        template<class Obj>
        Obj* create(LPCTSTR, const POINT&, const SIZE&);

        
};
template<class Obj>
Obj* CWindow::create(LPCTSTR lpText, const POINT& pos, const SIZE& size){
    Obj* o = new Obj(lpText, this, pos, size);
    if(!o->getHWND()){
        MessageBox(NULL, L"Error creating element for CWindow", L"Error", MB_OK | MB_ICONERROR);
        return nullptr;
    }else{
        //TODO необходимо зарегистрировать обьект в обработке событий!
        return o;
    }
}
LRESULT CWindow::customProc(UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
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
CWindow::CWindow(LPCTSTR lpDefinedText, LPCTSTR lpClassName, DWORD dwStyle, const POINT& pos, const SIZE& size, HINSTANCE hInst, HWND hWndParent = NULL) : CObject(lpClassName, dwStyle, hInst){
    this->_hWnd = CreateWindow(lpClassName, lpDefinedText, dwStyle, pos.x, pos.y, size.cx, size.cy, hWndParent, NULL, hInst, NULL);
}
#endif