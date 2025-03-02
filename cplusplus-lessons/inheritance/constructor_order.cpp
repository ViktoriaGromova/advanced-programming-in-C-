# include <iostream>

// Порядок вызовов конструкторов и дестукторов
// Order of constructors and destructors

// Если в классах есть нетривиальная создаваемая часть (например, структура A, B)

struct A
{
    A()
    {
        std::cout << "Create A"<< '\n';
    }

    ~A()
    {
        std::cout << "Delete A"<< '\n';
    }
};

struct B
{
    B()
    {
        std::cout << "Create B"<< '\n';
    }

    ~B()
    {
        std::cout << "Delete B"<< '\n';
    }
};

struct Mom{
    A a;
    Mom(){
        std::cout << "Create Mom"<< '\n';
    }

    ~Mom(){
          std::cout << "Delete Mom"<< '\n';
    }
};

struct Son : Mom{ // Когда создается Son, уже Mom создана.
    B b;
    Son(){
        std::cout << "Create Son"<< '\n';
    }

    ~Son(){
          std::cout << "Delete Son" << '\n';
    }
};

// Первым делом создаются поля, то есть первым делом создаться поле A у мамы, потом сам конструктор Mom,
// далее делаем настройку Mom с помощью Son, далее вызывается у B, потом Son

// Деструкторы работают в обратном порядке относительно конструкторов. Son-> поля Son -> Mom-> поля Mom


// Как инициализируются классы/структуры Son, когда конструктор нетривиальный.
// Если не указано явно, то будет при вызыве класса Son: если в конструкторе его явно не указано, как работать с Mom,
// то будет конструтор по умолчанию.
struct step_Mom
{
    int a;

    step_Mom() {
        std::cout << "Step Mom" << '\n';
    }

    step_Mom(int a) {
        std::cout << a << '\n';
    }
};

struct step_Daughter : step_Mom
{
    int y;
    step_Daughter(int x): step_Mom(a), y(x) { // будет вызван конструкор инициализации у step_Mom
        std::cout << x << '\n'; // списки лучше создавать в той последовательности, в которой они должны быть созданы
        // чтобы это инициализировать позволяло следующее поле. Например size и создание вектора этим размером.
    }

    // step_Daughter(int x) { // step_Mom не задан явно - будет вызван конструкор по умолчанию у step_Mom
    //     std::cout << x << '\n';
    // }
};


// Нельзя инициализировать класс конструктора, если он не является его прямым родителем 
struct Granny
{
    int a;
    Granny()
    {
        std::cout << "Create Granny" << '\n';
    }

    Granny(int x)
    {
        std::cout << x << '\n';
    }

    ~Granny()
    {
        std::cout << "Delete Granny" << '\n';
    }
};

struct Mommy: Granny
{
    int b;
    Mommy()
    {
        std::cout << "Create Mommy" << '\n';
    }

    Mommy(int y)
    {
        std::cout << y << '\n';
    }

    ~Mommy()
    {
        std::cout << "Delete Mommy" << '\n';
    }
};

struct Grandson : Mommy
{
    int c;

    using Mommy::Mommy // с c++11 Если мы так пишем, то мы говорим, что мы хотим создать конструкторы Son от всего чего
    // что используется в mom. При этом Son будет по умолчанию.

    Grandson()
    {
        std::cout << "Create Grandson" << '\n';
    }

    Grandson(int z): Granny(z), Mommy(z) // ошибка. Здесь нельзя проинициализировать Granny(z), так как она не является
    // его прямым родителем, только Mommy. Только через Mom можно проинициализировать Granny(z)
    {
        std::cout << z << '\n';
    }

    ~Grandson()
    {
        std::cout << "Delete Grandson" << '\n';
    }
};

int main(){
    Son s;
    return 0;
}