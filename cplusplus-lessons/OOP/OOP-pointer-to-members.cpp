#include <iostream>

// Pointer to members
// В c++ можно передавать указатели на члены и методы, а не только на объекты и функции
struct LineSegment
{
    double begin;
    double end;
    double fun1() { return 1; }
    double fun2() { return 2; }
};

// Можно делать вызовы методы с помощью таких ссылок 

void processSegment(LineSegment& s, bool inverted)
{
    double LineSegment::*begin = inverted ? &LineSegment::end : &LineSegment::begin;
    double LineSegment::*end = inverted ? &LineSegment::begin : &LineSegment::end;

    // Работа с указателями на методы. Типа какой может отработать метод.
    double (LineSegment::*fun)() = inverted ? &LineSegment::fun1 : &LineSegment::fun2;
    std::cout << (s.*fun)();
}

void processSegment(LineSegment* s, bool inverted) // Аналогично можно использовать ->
{
    double LineSegment::*begin = inverted ? &LineSegment::end : &LineSegment::begin;
    double LineSegment::*end = inverted ? &LineSegment::begin : &LineSegment::end;

    // Работа с указателями на методы. Типа какой может отработать метод.
    double (LineSegment::*fun)() = inverted ? &LineSegment::fun1 : &LineSegment::fun2;
    std::cout << (s->*fun)();
}

int main()
{
    double LineSegment::*p = &LineSegment::begin;

    LineSegment s{1.0, 2.0};

    // К данному объекту можно обратиться как указатель на член
    // Указатель на член. Хранит смещение относительно структуры. Она для всех объектов работает одинаково.

    std::cout << s.*p << std::endl; // .* - поомогает вывести объект 
    return 0;
}
