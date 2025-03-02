#pragma once

#include <cctype>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int32_t BASE = 1e9;
constexpr int8_t CHANKSIZE = 9;

class BigInteger {
public:
    enum class Sign;

    explicit BigInteger();
    BigInteger(const int32_t& number);
    BigInteger(const std::string& number);
    BigInteger(BigInteger::Sign sign);
    BigInteger(BigInteger::Sign sign, std::vector<uint32_t> number);
    BigInteger(const BigInteger& number);
    explicit operator int() const; 
    explicit operator bool() const; 

    bool is_equal(const BigInteger& number) const;
    bool is_greater_than(const BigInteger& number) const;
    BigInteger& operator+=(const BigInteger& number);
    BigInteger& operator-=(const BigInteger& number);
    BigInteger& operator*=(const BigInteger& number);
    BigInteger& operator/=(const BigInteger& number);
    BigInteger& operator%=(const BigInteger& number);
    BigInteger& operator=(const BigInteger& number);
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);
    std::string toString() const;

    friend std::istream &operator>>(std::istream &in, BigInteger &number);
private:
    Sign sign_value;
    std::vector<uint32_t> value;

    Sign sign(int32_t value) const;
    void abs_sum(const BigInteger& number);
    void abs_sub(const BigInteger& number);
    bool isNotZeroVector(const std::vector<uint32_t>& number) const;
};