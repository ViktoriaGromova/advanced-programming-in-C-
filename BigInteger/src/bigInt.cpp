#include "../include/bigInt.hpp"
#include <iostream>
#include <string>

enum class BigInteger::Sign { POSITIVE = 1, NEGATIVE = -1, ZERO = 0 };

BigInteger::Sign BigInteger::sign(const int32_t value)
{
    if (value == 0) {
        return BigInteger::Sign::ZERO;
    }
    if (value < 0) {
        return BigInteger::Sign::NEGATIVE;
    }
    return BigInteger::Sign::POSITIVE;
}

BigInteger::BigInteger(): sign_value(BigInteger::Sign::ZERO) { }

BigInteger::BigInteger(const int32_t& value)
{
    sign_value = sign(value);
    if (sign_value == BigInteger::Sign::ZERO)
        return;
    else {
        uint32_t absValue = value;
        if (sign_value == BigInteger::Sign::NEGATIVE) {
            absValue = -value;
        }

        while (absValue > 0) {
            number.push_back(absValue % BASE);
            absValue /= BASE;
        }
    }
}

BigInteger::BigInteger(const std::string& number) {
    
 }