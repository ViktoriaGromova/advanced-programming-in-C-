#include <iostream>

// Cписки  инициализации  - часть определения
class A{
    const int& a;
    // A() = delete;
public: 
    // A(const int& a) a(a) {} // rvalue
};

// void f(){
//     A a(5);
// }

class B{
 int x;
 int& x1;
 A a;
 // Нельзя свободно проинициализировать, так как нет ссылки по умолчанию.
 // Чтобы не было SE мы можем сначала до того, как начало работать тело конструктора
 // объявить значения переменных, а только потом переходить в тело конструктора.
 B(): x(1){}
};

class String
{

};
