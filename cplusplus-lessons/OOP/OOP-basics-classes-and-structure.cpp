#include <iostream>

class Myclass
{
private:
    // Fields - если не указать, то инициализируется рандомным числом или значение по умолчанию;
    int* x = nullptr;
    int m = 0;
public:
    // Methods
    void print(int a)
    {
        std::cout << a << std::endl;
    }
    // Можно реализовывать методы класс вне класса, но объявить надо в самом классе
    void print_f(int a);
};

void Myclass::print_f(int a){
    std::cout << a + 1 << std::endl;
}

int main(){
    Myclass mc = Myclass();
    mc.print(1);
    mc.print_f(1);
    return 0;
}