#include <iostream>
#include <cstring>

// Правило трех: 
// Если в классе реализовывается одно из: конструктор копирования, деструктор или оператор 
// присваивания, то необходимо, чтобы все три вещи были реализованны в классе.

// операторы  -  функция, которая должна что-то возвращать

class String{
    size_t size = 0;
    char* str = nullptr;
    
void swap(String& string){
    std::swap(str, string.str);
    std::swap(size, string.size);
}
public: 

String() = default;

String(char ch, size_t size){
    this->size = size;
    str = new char[size];
    memset(str, ch, size);
}

String(const String& string){
    size = string.size;
    str = new char[string.size];
    memcpy(str, string.str, size);
}

// Операторы

// Оператор присваивания
// Общий вид: ... operator=(). Можно сделать через = default;
// ...& operator=() = default;

// Не очень хорошее представление, так как тут идет дублирование кода. Это плохо.
String& operator=(const String& string){ // &в возвращаемом типе говорит о том, что мы не делаем
                                         // лишний раз копирование,а возвращаем, то что получили 
    if(this == &string) return *this;    // Если я хочу самой себе сделать присваивание s = s;
    delete[] str; // Можно заменить на this->~String(); - UB
    size = string.size;
    str = new char[string.size];
    memcpy(str, string.str, size);
    return *this;
}

// Представление оператора присваивания через copy and swap. Позволяет реализовать операторы, устойчивые
// к исключениям. Для реализации необходимо реализовать: конструктор копирования, оператор присваивания,
// функцию swap noexcept 
String& operator=(const String& string){
    if(this == &string) return *this;
    String temp_string = string; // deep copy
    swap(temp_string);
    return *this;
}

// Если убрать ссылку и const, то можно переписать и переделать как: 
String& operator=(String string){
    swap(string);
    return *this;
}

// Оператор присваивания может быть для const или не для const, но автоматически с const обычно работает

~String(){
    delete[] str;
}

};

int main(){
    int x = x; // Это эквивалентно просто int x;
    String s = s; // Вызовится конструктор копирования от себя самого. НЕ ПИШИ ТАК. 
    // Упоротый способ создать объект, у которого есть все конструкторы запрещены.
    return 0;
}