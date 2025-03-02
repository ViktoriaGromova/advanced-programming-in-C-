#include <iostream>

// Поток ввода/вывода  с помощью операторв >> или << от двух операндов: поток и объект. Так как левый операнд - поток, то его нужно определять вне класса
class String
{
    friend std::istream &operator>>(std::istream &in, BigInteger &number);
};

std::ostream &operator<<(std::ostream &out, const BigInteger &number)
{
    out << number.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &number)
{
    in >>;
    return in;
}