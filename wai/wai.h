#ifndef _WAI_
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE  
#endif
#ifndef _WINDOWS_
#include <windows.h>
#endif


class wai{
    public:
        wai(HINSTANCE, LPCTSTR, WNDPROC);
        bool isRegistered = false;
    private:
        HINSTANCE   _hInstance;
        LPCTSTR     _lpClassName;
        WNDCLASS    _wcStruct = {0};

};
wai::wai(HINSTANCE hInst, LPCTSTR lpClassName, WNDPROC fnUserFnc) : _hInstance(hInst), _lpClassName(lpClassName){
    this->_wcStruct.lpszClassName = this->_lpClassName;
    this->_wcStruct.lpfnWndProc = (WNDPROC)fnUserFnc;
    this->_wcStruct.style = CS_HREDRAW | CS_VREDRAW;
    this->_wcStruct.hInstance = this->_hInstance;
    this->_wcStruct.hCursor = LoadCursor(NULL, IDC_ARROW);
    this->_wcStruct.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;

    this->isRegistered = RegisterClass(&this->_wcStruct);
}
#endif