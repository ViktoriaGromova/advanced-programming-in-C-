#pragma once
#include <vector>
#include <ostream>
#include <string>

class BigInteger
{
    bool isNegative;
    long long int mode = 1e9;
    std::vector<long long int> Number;

public:
    BigInteger(const long long int x);
    BigInteger(bool isNegative, std::vector<long long int> Number) : isNegative(isNegative), Number(Number) {}
    BigInteger() : isNegative(false), Number{0} {}
    BigInteger &operator=(const BigInteger &x);
    BigInteger &operator+=(const BigInteger &x);
    BigInteger operator+(const BigInteger &x);
    BigInteger abs() const;
    std::string toString();
    void Norm();
    bool isGreater(const BigInteger &x);
};