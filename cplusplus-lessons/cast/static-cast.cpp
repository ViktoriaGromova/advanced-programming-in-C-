#include<iostream>

void f(int) { std::cout << 1 << std::endl; }
void f(double) { std::cout << 2 << std::endl; }

int main(){
    // static_cast
    // Создает новые объект
    int x = 0;

    f(static_cast<double>(x));
    return 0;
}