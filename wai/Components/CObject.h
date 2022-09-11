#include <windows.h>
#ifndef _WAI_CObjects
#define _WAI_CObjects
class CObject{
    public:
        CObject(LPCTSTR, DWORD, HINSTANCE);

        const HWND getHWND(){
            return this->_hWnd;
        }
    protected:
        DWORD       _dwStyle;
        LPCTSTR     _lpClassName;
        HINSTANCE   _hInst;
        HWND        _hWnd = NULL;
};
/**
 * @brief Конструктор обьекта CObject
 * 
 * @param lpClassName имя класса
 * @param dwStyle стиль обьекта
 * @param hInst дескриптор
 */
CObject::CObject(LPCTSTR lpClassName, DWORD dwStyle, HINSTANCE hInst) : _dwStyle(dwStyle), _lpClassName(lpClassName), _hInst(hInst){}
#endif