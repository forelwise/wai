#ifndef _WAI_
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE  
#endif

#include <windows.h>
#include <map>
#include "Components/CObject.h"
#include "Components/CWindow.h"
class wai{
    public:
        wai(HINSTANCE, LPCTSTR, WNDPROC);
        bool isRegistered = false;
        template<class Obj>
        Obj* create(LPCTSTR, DWORD, int, int, int, int);

        LRESULT CALLBACK appProc(HWND, UINT, WPARAM, LPARAM);
        
    private:
        HINSTANCE   _hInstance;
        LPCTSTR     _lpClassName;
        WNDCLASS    _wcStruct = {0};
        
        std::map<HWND, CObject*> _objectRegistry; // Конвеер - Список указатель на все обьекты для обработчика событий(сообщений)
        void        _pushToRegistry(CObject*);
        //TODO std::unique_ptr добавить для обьектов в конвеере
        //возможны ошибки из-за реаллоцирования памяти(один обьект указывает на другой см. https://habr.com/ru/post/664044/)
        //Найти нужный HWND в НЕСКОЛЬКИХ списках обьектов, далее получить нужный обьект, и передать ему управление над сообщениями:
        //PROBLEM - пока не разобрался как при таких действиях сохранить структуру дочернего после преобразования из родительского...см. Проблема пребразования.cpp
};
/**
 * @brief Добавляет созданный обьект в конвеер обработчика событий
 * 
 * @param obj добавляемый обьект
 */
void wai::_pushToRegistry(CObject* obj){
    this->_objectRegistry.insert(std::pair<HWND, CObject*>(obj->getHWND(), obj));
}

/**
 * @brief Обработчик событий для приложения. Вызывается перед пользовательской обработкой, на пользователе остается вызвать defWindowProc
 * 
 * @param hWnd дескриптор
 * @param msg сообщение
 * @param wParam 
 * @param lParam 
 * @return LRESULT 
 */
LRESULT CALLBACK wai::appProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    auto find_object = this->_objectRegistry.find(hWnd);
    if(find_object == this->_objectRegistry.end()) //Если обьекта с данным HWND нет в конвеере то обрабатывать нечего
        return 0;
    switch(msg){
        case WM_DESTROY: 
            //в map хранятся ссылки на CObject родительский класс
            //Возможно использование dynamic_cast? см. https://habr.com/ru/post/347786/
            CWindow* A = static_cast<CWindow*>(find_object->second);
            A->onClose();
            //PROBLEM в дальнейшем с различными событиями необходимо знать к какому типу то приводить
            //EXAMPLE: WM_MOVE работать должно как на CButton, CEdit так и на CWindow
            //TODO возможен ли обработчик событий внутри каждого обьекта???
        break;
    }
    return 0;
}


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
 * @return Obj* указатель на только что созданный обьект пользователю или NULL при неудаче
 */
template<class Obj>
Obj* wai::create(LPCTSTR lpDefinedText, DWORD dwStyle, int x, int y, int width, int height){
    Obj* o = new Obj(lpDefinedText, this->_lpClassName, dwStyle, x, y, width, height, this->_hInstance);
    if(!o->getHWND()) 
        return NULL;

    this->_pushToRegistry(o);
    return o;
    //TODO возможна утечка памяти т.к. указатель не удаляется ????????????
}
/**
 * @brief Конструктор обьекта-приложения Windows API Interface
 * 
 * @param hInst дескриптор 
 * @param lpClassName имя класса
 * @param fnUserFnc функция для обработки сообщений
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