#include <iostream>

//  Наследование 
//  Некоторые типы, могут быть подтипами другого типа.
// Public, private, protected

// По умолчанию наследование приватное по умолчанию, а у структур публичное

class Base{
private:
    int c = 1;
protected:
    int r = 9;
public:
    int a = 0;
    void f(){
        std::cout << "Base class\n";
    }
    friend int main(); // friend не наследуется 
};

class Derived: public Base{
public:
    int b = 1;
    void g(const Base& x, const Derived& v){
        std::cout << "Derive\n";
        x.r; // так как поле принятное const Base& x,, то тут не работает 
        v.r; // Однако, если я возьму от самого себя в форме объекта,то тут будет работать
    } 
};

class Derived2: protected Base{
public:
friend int main();
    int b = 1;
    void g(){
        std::cout << "Derive\n";
    } 
    //std:: c  В наследниках нельзя наследоваться от private полей
};

class SubDerived: public Derived2{
    void k(){
        std::cout << r;
    }
};

// compile time metod

int main(){
    Derived d;
    d.g();
    d.f();
    Derived2 d1;
    std::cout << d1.b << std::endl;
// Можно обратиться к полю
d.b = 4;
std::cout << d.a << std::endl;
}