#ifndef _WAI_
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE  
#endif

#include <windows.h>
#include <vector>
#include "Components/CObject.h"
#include "Components/CWindow.h"
class wai{
    public:
        wai(HINSTANCE, LPCTSTR, WNDPROC);
        bool isRegistered = false;
        template<class Obj>
        Obj* create(LPCTSTR, DWORD, int, int, int, int);
        
    private:
        HINSTANCE   _hInstance;
        LPCTSTR     _lpClassName;
        WNDCLASS    _wcStruct = {0};
        
        std::vector<CObject*> _objectRegistry; // Список указатель на все обьекты для обработчика событий(сообщений)
        //TODO std::unique_ptr добавить для обьектов в конвеере
};
/**
 * @brief Создает родительский элемент 
 * 
 * @tparam Obj 
 * @param lpDefinedText - текст используемый в элементах (Заголовок окна, текст кнопки, и т.д.)
 * @param dwStyle - стиль элемента  
 * @param x позиция Х
 * @param y позиция Y
 * @param width ширина
 * @param height высота
 * @return Obj* указатель на только что созданный обьект пользователю
 */
template<class Obj>
Obj* wai::create(LPCTSTR lpDefinedText, DWORD dwStyle, int x, int y, int width, int height){
    return new Obj(lpDefinedText, this->_lpClassName, dwStyle, x, y, width, height, this->_hInstance);
}






/**
 * @brief Конструктор обьекта-приложения Windows API Interface
 * 
 * @param hInst дескриптор 
 * @param lpClassName имя класса
 * @param fnUserFnc функция для обработки сообщений
 * //TODO функция обработки сообщений должна быть статична, возможно ли обойти это?
 */
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