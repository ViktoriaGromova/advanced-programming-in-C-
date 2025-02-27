#include <iostream>

struct Granny
{
    int g = 1;
};

struct Mom: public Granny
{
    int m = 2;
};

struct Son: public Mom, public Granny{
    int s = 3;
};

int main(){
    Son s;
    // [[[g]m] [g] s]
    // Такая ситуация назвается невидимый(недоступный) базовый класс. Будет заполнять Granny, которыя наследуется сыном память
    // Проблема в том, что к [g], который в s должен иметься нет никакого человеческого способа обратиться (s.g), однако к Mom мы можем обратиться s.Mom::g
    // через реинтерпрет каст и сдвига конечно можно :)

    // СНачала g - решает какой g, а потом приватность проверяется и даже если сделать struct Son: public Mom, private Granny{
    std::cout << s.g << std::endl; // CE из-за прямого наследование granny
    return 0;
}