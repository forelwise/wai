#include <iostream>
using namespace std;

class C{
    protected:
        int i;
    public:
        void test(){
            cout << i;
        }   
        C(int _i):i(_i){}
};
class B : public C{
    public:
        B(int j) : C(j){
            
        }
};

class A{
    public:
    template<typename T>
    T* get(int j){
        return new T(j);
    }
};

int main(){
    A control;
    B* test = control.get<B>(21);
    test->test();
    return 0;
}