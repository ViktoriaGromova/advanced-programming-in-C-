#include <iostream>

struct Mom
{
    void f() { std::cout << "Mom::f()" << std::endl; }
    int m = 1;
};

struct Dad
{
    void f() { std::cout << "Dad::f()" << std::endl; }
    int d = 2;
};

struct Son: public Mom, public Dad{
    int s = 3;
};

int main(){
    Son s;
    // [ Mom::m ][ Dad::d ][ Son::s ] - зависит от того, что первее прописсывается после :
    std::cout << sizeof(s) << std::endl;
    std::cout << &s.m << " " << &s.d << " "<< &s.s << std::endl;
    // 0x7ffd41f315bc 0x7ffd41f315c0 0x7ffd41f315c4 -  разница между ними в 4 байта

    // тут будет ошибка, так как у мамы и у папы равноценные функции. И в граффе наследников, то обе подходят
    //s.f();

    s.Mom::f();
}