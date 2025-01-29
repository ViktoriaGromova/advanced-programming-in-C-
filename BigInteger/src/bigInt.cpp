#include "../include/bigInt.hpp"

#include <iostream>
#include <string>

struct IncorrectValue { };

enum class BigInteger::Sign { POSITIVE = 1, NEGATIVE = -1, ZERO = 0 };

BigInteger::Sign BigInteger::sign(const int32_t value) const
{
    if (value == 0) {
        return BigInteger::Sign::ZERO;
    }
    if (value < 0) {
        return BigInteger::Sign::NEGATIVE;
    }
    return BigInteger::Sign::POSITIVE;
}

BigInteger::BigInteger(): sign_value(BigInteger::Sign::ZERO), value({0}) { }

BigInteger::BigInteger(const int32_t& number)
{
    sign_value = sign(number);
    if (sign_value == BigInteger::Sign::ZERO) {
        BigInteger();
    } else {
        uint32_t absValue = number;
        if (sign_value == BigInteger::Sign::NEGATIVE) {
            absValue = -number;
        }

        while (absValue > 0) {
            value.push_back(absValue % BASE);
            absValue /= BASE;
        }
    }
}

BigInteger::BigInteger(const std::string& number)
{
    if (number.empty() || number == "0") {
        BigInteger();
        return;
    }

    size_t size_not_numeric_symbols = 0;
    if (number[0] == '-') {
        sign_value = BigInteger::Sign::NEGATIVE;
        size_not_numeric_symbols = 1;
    } else {
        sign_value = BigInteger::Sign::POSITIVE;
        if (number[0] == '+') {
            size_not_numeric_symbols = 1;
        }
    }

    while (number[size_not_numeric_symbols] == '0') {
        ++size_not_numeric_symbols;
    }

    if (size_not_numeric_symbols == number.size()) {
        BigInteger();
        return;
    }

    value.resize((size_not_numeric_symbols + CHANKSIZE - 1) / CHANKSIZE);

    for (size_t i = number.size(); i > size_not_numeric_symbols; --i) {
        value[(i - size_not_numeric_symbols - 1) / CHANKSIZE] =
            value[(i - size_not_numeric_symbols - 1) / CHANKSIZE] * 10 +
            number[number.size() + size_not_numeric_symbols - i] - '0';
    }
}

BigInteger::BigInteger(BigInteger::Sign sign)
{
    if (sign != BigInteger::Sign::ZERO) {
        throw IncorrectValue();
    }
    BigInteger();
}

bool BigInteger::isNotZeroVector(const std::vector<uint32_t>& number) const
{
    for (const uint32_t& num: number) {
        if (num != 0) {
            return true;
        }
    }
    return false;
}

BigInteger::BigInteger(BigInteger::Sign sign, std::vector<uint32_t> number)
{
    if ((sign == BigInteger::Sign::ZERO && (number.size() != 1 && !isNotZeroVector(number))) || (sign == BigInteger::Sign::ZERO && isNotZeroVector(number))) {
        throw IncorrectValue();
    }
    // TODO: Make a function that removes extra zeros if they are at the beginning
    sign_value = sign;
    value = number;
}

std::String BigInteger::toString(){}