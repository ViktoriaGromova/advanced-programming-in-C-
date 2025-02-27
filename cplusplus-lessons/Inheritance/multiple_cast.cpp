#include <iostream>

struct Granny
{
    void f(int);
    int g = 1;
};

struct Dad: public Granny
{
    int d = 2;
};

struct Mom: public Granny
{
    int m = 2;
};

struct Son: public Mom, public Dad{
    int s = 3;
};

int main(){
    Son s;
    // [ Mom::g ][ Mom::m ][ Dad::g ][ Dad::d ][ Son::s ]- такое расположение дает возможность делать касты без каких либо вычислительных затрат (Это было на собесе)

    // Тут будет происходить сдвиг указателя с начала класса к началу dad: [ Dad::g ][ Dad::d ][ Son::s ]
    Dad *d=&s;
    // Аналогично 
    Dad &pd=s;

    // 0x7fff19f090d0 0x7fff19f090d8
    std::cout << &s << " " << d << std::endl;

    Son* ss = static_cast<Son*>(d); // Так как множественное наследование, то компилятор понимает, что тут чтобы был каст вниз и компилятор понимает

    // Однако с Granny не полуится, так как их две
    return 0;
}