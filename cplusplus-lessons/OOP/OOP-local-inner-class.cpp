# include <iostream>

class A {
    class Inner{
public:
    int x = 0;
    };


public:
    class pubInner{
        public:
        pubInner() = default;
    };
    Inner GetInner(){
        return Inner();
    }
};

// Локальные классы внутри функций
// К примеру, мы хотим объявить все в виде функций и мы хотим объявить компаротор, и хочется его объявить где-то поближе к функции. И нужно как-то быстро сделать с помощью локальных функций, в которых все определить

int main(){
    A::pubInner a;
    A a1;
    auto in = a1.GetInner();
    a1.GetInner().x;

    class local{
    public:
        int x = 0;
    };
    return 0;
}
