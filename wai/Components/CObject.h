#ifndef _WAI_CObjects
#define _WAI_CObjects
#include <windows.h>
#include "Define.h"
class CObject{
    public:
        CObject(LPCTSTR, DWORD, HINSTANCE);

        const HWND getHWND(){
            return this->_hWnd;
        }
        virtual LRESULT customProc(UINT, WPARAM, LPARAM) = 0;
        void defaultProc(UINT, WPARAM, LPARAM); //Функция для обработки базовых сообщений
        //TODO необходимо разорабться все ли события подходят для всех обьектов, если да то в func defaultProc необходимости нет
        //если есть кастомные, их необходимо выносить в отдельный класс обьекта

        //Default Events:
           
    protected:
        DWORD       _dwStyle;
        LPCTSTR     _lpClassName;
        HINSTANCE   _hInst;
        HWND        _hWnd = NULL;
};
/**
 * @brief Обработчик дефолтных событий 
 * 
 * @param msg событие
 * @param wParam параметр 1
 * @param lParam параметр 2
 */
void CObject::defaultProc(UINT msg, WPARAM wParam, LPARAM lParam){
    /*switch(msg){
        case WM_LBUTTONDOWN:
            if(this->onMouseDown != nullptr) 
                this->onMouseDown(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_LBM, wParam);
        break;
        case WM_LBUTTONUP:
            if(this->onMouseDown != nullptr) 
                this->onMouseUp(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_LBM, wParam);
        break;
        case WM_RBUTTONDOWN:
            if(this->onMouseDown != nullptr) 
                this->onMouseDown(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_RBM, wParam);
        break;
        case WM_RBUTTONUP:
            if(this->onMouseDown != nullptr) 
                this->onMouseUp(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_RBM, wParam);
        break;
        case WM_MBUTTONDOWN:
            if(this->onMouseDown != nullptr) 
                this->onMouseDown(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_MBM, wParam);
        break;
        case WM_MBUTTONUP:
            if(this->onMouseDown != nullptr) 
                this->onMouseUp(POINT({HIWORD(lParam), LOWORD(lParam)}), WE_MBM, wParam);
        break;
        case WM_DESTROY:
            if(this->onDestroy != nullptr)
                this->onDestroy();
        break;
        default:    
            DefWindowProc(this->getHWND(), msg, wParam, lParam);
        break;
    }*/
    //  this->customProc(msg, wParam, lParam);
}
/**
 * @brief Конструктор обьекта CObject
 * 
 * @param lpClassName имя класса
 * @param dwStyle стиль обьекта
 * @param hInst дескриптор
 */
CObject::CObject(LPCTSTR lpClassName, DWORD dwStyle, HINSTANCE hInst) : _dwStyle(dwStyle), _lpClassName(lpClassName), _hInst(hInst){}
#endif