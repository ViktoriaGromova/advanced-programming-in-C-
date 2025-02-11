#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

// Functional call overloading, comparators
// operator() - любой возвращаемый тип и для любого количества входных значений
// можно использовать в стандартом алгоритме
// Пегрузка функциональных вызовов и компараторов 
// Для своих классов можно переопределить функциональный вызов. Тогда объекты класса можно использовать как функции.

class GreaterThanZero{ // Функциональный класс
public:
    bool operator() (int x) {
        return x > 0;
    }
};

// Компаратор - это объект, который обладает оператор круглые скобки, работающий как сравнения.

class MyCompare{
public:
        bool operator() (int x, int y){ // Необходимо реализовывать в компаратор именно меньше, и надо передавать в map и 
            return abs(x) < abs(y);
        }
};

int main(){
    GreaterThanZero gtz; // функутор
    std::cout << gtz(3);

    std::vector<int> v = {-2, 0, 3, -1, 5};
    std:: cout << *std::find_if(v.begin(), v.end(), GreaterThanZero()); // требует придикат - объект, который ведет себя как функция
    //  ищет первое число в векторе, которое больше нуля, используя предикат GreaterThanZero

    std::map<int, int, MyCompare> m; // Тип компаратор 
    std::sort(v.begin(), v.end(), MyCompare()); // Сортировка через компаратор
    return 0;
}