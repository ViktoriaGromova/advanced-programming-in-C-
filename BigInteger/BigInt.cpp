#include "BigInt.h"
#include <iostream>
#include <vector>
#include <string>

BigInteger::BigInteger(long long int x)
{
    isNegative = (x < 0);
    if (isNegative)
    { 
        x *= -1;
    }

    do
    {
        Number.push_back(x % mode);
        x /= mode;
    } while (x);
}

BigInteger BigInteger::abs() const
{
    return BigInteger(false, this->Number);
}

void BigInteger::Norm()
{
    int carrier = 0;
    for (int i = 0; i < Number.size(); ++i)
    {
        int64_t temp = Number[i] + carrier;
        carrier = temp / mode;
        Number[i] = temp % mode;
    }

    if (carrier > 0)
    {
        Number.push_back(carrier);
    }

    while (Number.back() == 0 && Number.size() > 1)
    {
        Number.pop_back();
    }
}

BigInteger &BigInteger::operator+=(const BigInteger &x)
{
    if (!(isNegative ^ x.isNegative))
    {
        for (size_t i = 0; i < x.Number.size(); ++i)
        {
            if (i >= Number.size())
            {
                Number.push_back(x.Number[i]);
            }
            else
            {
                Number[i] += x.Number[i];
            }
        }
        Norm();
        return *this;
    }

    if ((*this).abs().isGreater(x.abs()))
    {
        for (size_t i = 0; i < x.Number.size(); ++i) 
        {
            Number[i] -= x.Number[i];
        }
        Norm();
        return *this;
    }


    std::cout<<"here2";
    isNegative = !isNegative;
    std::vector<long long int> NewNumber = x.Number; 
    for (size_t i = 0; i < Number.size(); ++i)
    {
        NewNumber[i] -= Number[i];
    }
    Number = NewNumber;
 
    Norm();
    return *this;
}

BigInteger &BigInteger::operator++()
{
    return (*this) += 1;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger copy_x = *this;
    ++(*this);
    return copy_x;
}

BigInteger &BigInteger::operator--()
{
    return (*this) -= 1;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger copy_x = *this;
    --(*this);
    return copy_x;
}

BigInteger BigInteger::operator+(const BigInteger &x)
{
    BigInteger new_x = *this;
    new_x += x;
    return new_x;
}

BigInteger BigInteger::operator-(const BigInteger &x){
    BigInteger new_x = *this;
    new_x += x;
    return new_x;
}

// global
BigInteger operator+(const BigInteger &x, const BigInteger &y) // x + y
{
    BigInteger new_x = x;
    new_x += y;
    return new_x;
}

// global
BigInteger operator-(const BigInteger &x, const BigInteger &y) // x - y
{
    BigInteger new_x = x;
    new_x -= y;
    return new_x;
}

BigInteger &BigInteger::operator=(const BigInteger &x) 
{
    if (this == &x)
    {
        return *this;
    }
    isNegative = x.isNegative;
    Number = x.Number;
    return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &x)
{
    BigInteger inv_x(!x.isNegative, x.Number);
    (*this) += inv_x;
    return *this;
}

std::ostream &operator<<(std::ostream &out, BigInteger &x) // output
{
    out << x.toString();
    return out;
}

std::string BigInteger::toString()
{
    std::string str;
    if (isNegative)
    {
        str += '-';
    }

    for (auto it = Number.rbegin(); it != Number.rend(); ++it)
    {
        str += std::to_string(*it);
    }
    return str;
}       

bool BigInteger::isGreater(const BigInteger &x) const{

    if (isNegative != x.isNegative)
    {
        return !isNegative;
    }

    if (Number.size() > x.Number.size()){
        return true;
    }
    if(Number.size() < x.Number.size()){
        return false;
    }

    for(int i = Number.size(); i != 0; --i){
        if ((*this).Number[i-1] > x.Number[i-1]){
            return true;
        }
    }
    return false;
}

bool BigInteger::isEqual(const BigInteger &x) const
{
    return (x.Number == Number && x.isNegative == isNegative);
}

bool operator==(const BigInteger &x, const BigInteger &y)
{
    return x.isEqual(y);
}

bool operator!=(const BigInteger &x, const BigInteger &y)
{
    return !x.isEqual(y);
}

bool operator>(const BigInteger &x, const BigInteger &y)
{
    return x.isGreater(y);
}

bool operator<(const BigInteger &x, const BigInteger &y)
{
    return y.isGreater(x);
}

bool operator>=(const BigInteger &x, const BigInteger &y)
{
    return x == y || x > y;
}

bool operator<=(const BigInteger &x, const BigInteger &y)
{
    return x == y || x < y;
}