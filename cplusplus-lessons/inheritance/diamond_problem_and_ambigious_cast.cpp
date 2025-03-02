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
    // Такая ситуация назвается ромбовидное наследование или diamond_problem.
    // Если у вас есть прородитель, который унаследован дважды или более раз через промежуточных родителей, то при обращении к его полям и методам будет получатся неоднозначности ЦЕ
    // Решить можно указать конкретную область s.Mom::f() например. Однако s.Granny::f() - будет ЦЕ так как бабушек две

    // [[[g] Dad ][[g] Mom ] Son]  
    std::cout << s.g << std::endl;
    // Создается два отдельных, независимых g для mom и для dad отдельно, поэтому что CE - не понятно какую использовать
    std::cout << s.f() << std::endl;
    return 0;
}