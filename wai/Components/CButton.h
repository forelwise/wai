/**
 * @file CButton.h
 * @author KarmA
 * @brief Обьект кнопка / Button component * WindowApiInterface(WAI)
 * @version 0.1
 * @date 2022-09-12
 * @copyright Copyright (c) 2022
 */
#ifndef _WAI_CButton_
#define _WAI_CButton_
#include <windows.h>
#include "CObject.h"    
class CButton : public CObject{
    public:
        CButton(LPCTSTR, CObject*, const POINT&, const SIZE&);
        LRESULT customProc(UINT, WPARAM, LPARAM);

        void (*onClick)() = nullptr;
    private:
        CObject*    _parent;
        POINT       _position;
        SIZE        _size;
};
LRESULT CButton::customProc(UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_LBUTTONDOWN:
            if(this->onClick != nullptr)
                this->onClick();
        break;
        default:    
            return DefWindowProc(this->getHWND(), msg, wParam, lParam);
    }
    return 0;
}
CButton::CButton(LPCTSTR lpButtonText, CObject* parent, const POINT& pos, const SIZE& size) : 
CObject(L"BUTTON", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, (HINSTANCE)GetWindowLongPtr(parent->getHWND(), GWLP_HINSTANCE)){
    this->_hWnd = CreateWindow(L"BUTTON", lpButtonText, this->_dwStyle, pos.x, pos.y, size.cx, size.cy, parent->getHWND(), NULL, this->_hInst, NULL);
    this->_parent = parent;
}
#endif
