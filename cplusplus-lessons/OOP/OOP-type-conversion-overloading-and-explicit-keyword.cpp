#include <iostream>

class UserId{
    int id = 0;
    friend int operator+(UserId a, UserId b);
public:

    // explixit // чтобы запрещать неявные касты
    // ПРАВИЛО EXPLICIT: если вы хотите содзавать конструктор с одним аргументом, то не хотите сделать ли его explicit
    // explicit говорит нам о том, что мы хотим использовать явные касты и запрещать неявные вызовы 
    // explicit также можно применять с конструкторами от одного аргумента
    UserId(const int& id): id(id){} // Пользовательский каст  - плохо.
    //У операторов каста не пишется приводимых типу
    explicit operator int (){ // Запрещает неявные касты
        return id;
    }
};

int  operator+(UserId a, UserId b){
    return a.id + b.id + 1; 
}

// Literal suffixes overloading (since c++11)

// Мы хотим точно определить значение. Чтобы кодировать к примеру силу, секунды. И тут была строгая типизация. Чтобы случаной не сложить секунды с метрами.
// Я хочу реализовать std::cout << id + 1_uid; - и 1_uid - является переменной, которой относится к Literal suffixes
// Если char "abc"_uid

UserId operator ""_uid(unsigned long long x){ // тут надо аккуратно с типами данных потому что int нельзя и нужно 
    return UserId(x); 
}

// Contextual conversion к примеру, если мы хотим explicit к bool, и потом хотим к if (x ) // типа неявный, хотя это Contextual conversion, и явно можно не указывать

int main(){
    UserId a = 1; // через explicit не получится, так как я говорю, что присвой к UserId шiny
    // Будет правильным, если вызывать через 
    UserId  a(1); // Явный каст
    UserId id = UserId(1);
    std::cout << id + 1_uid;
    std::cout << a + 1; // так как мы скастовали к int, и показали как это сделать, и тут неявный каст
    std::cout<< static_cast<int>(a) + 1 << std::endl;
}