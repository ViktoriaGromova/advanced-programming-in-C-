#include "../include/bigInt.hpp"

#include <iostream>
#include <string>

struct IncorrectValue { };
struct DivisionByZero { };
struct UnsupportedValue { };

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
        ++size_not_numeric_symbols;
    } else {
        sign_value = BigInteger::Sign::POSITIVE;
        if (number[0] == '+') {
            ++size_not_numeric_symbols;
        }
    }

    while (number[size_not_numeric_symbols] == '0') {
        ++size_not_numeric_symbols;
    }

    if (size_not_numeric_symbols == number.size()) {
        BigInteger();
        return;
    }

    value.resize((number.size() - size_not_numeric_symbols + CHANKSIZE - 1) / CHANKSIZE);

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
    if ((sign == BigInteger::Sign::ZERO && (number.size() != 1 && !isNotZeroVector(number))) ||
        (sign == BigInteger::Sign::ZERO && isNotZeroVector(number))) {
        throw IncorrectValue();
    }
    // TODO: Make a function that removes extra zeros if they are at the beginning
    sign_value = sign;
    value = number;
}

BigInteger::BigInteger(const BigInteger& number)
{
    this->sign_value = number.sign_value;
    this->value = number.value;
}

void BigInteger::abs_sum(const BigInteger& number)
{
    const size_t max_size = number.value.size() > value.size() ? number.value.size() : value.size();

    BigInteger new_number = number;
    if (max_size != value.size()) {
        value.resize(max_size, 0);
    } else {
        new_number.value.resize(max_size, 0);
    }

    int32_t carry = 0;
    for (size_t i = 0; i < value.size(); ++i) {
        int64_t tem_sum = value[i] + new_number.value[i] + carry;
        value[i] = tem_sum % BASE;
        carry = tem_sum / BASE;
    }

    if (carry != 0) {
        value.push_back(carry);
    }
}

void BigInteger::abs_sub(const BigInteger& number)
{
    if (number.value == value) {
        *this = BigInteger();
        return;
    }

    // We assume that this object is larger than the input object.
    BigInteger abs_greater_big_int(BigInteger::Sign::POSITIVE, value);
    BigInteger abs_big_int(BigInteger::Sign::POSITIVE, number.value);
    if (abs_big_int.is_greater_than(abs_greater_big_int)) {
        BigInteger temp = abs_greater_big_int;
        abs_greater_big_int = abs_big_int;
        abs_big_int = temp;
    }

    const size_t min_size = abs_big_int.value.size();
    const size_t max_size = abs_greater_big_int.value.size();

    // The result is written in a larger numbe
    int32_t carry = 0;
    for (int i = 0; i < min_size; ++i) {
        if (carry) {
            if (abs_greater_big_int.value[i] - carry < 0) {
                abs_greater_big_int.value[i] += BASE;
                carry = 1;
            } else {
                carry = 0;
            }
        }

        if (abs_greater_big_int.value[i] < abs_big_int.value[i]) {
            carry = 1;
            abs_greater_big_int.value[i] += BASE;
        }
        abs_greater_big_int.value[i] -= abs_big_int.value[i];
    }

    // number remainder processing
    size_t remainder = min_size;
    while (carry) {
        if (abs_greater_big_int.value[remainder] - carry < 0) {
            ++remainder;
        } else {
            abs_greater_big_int.value[remainder] -= carry;
            carry = 0;
        }
    }

    while (abs_greater_big_int.value[abs_greater_big_int.value.size() - 1] == 0) {
        abs_greater_big_int.value.pop_back();
    }

    value = abs_greater_big_int.value;
}

bool BigInteger::is_greater_than(const BigInteger& number) const
{
    if (sign_value == BigInteger::Sign::ZERO && number.sign_value == BigInteger::Sign::ZERO) {
        return false;
    }

    if (number.sign_value != sign_value) {
        if (sign_value == BigInteger::Sign::NEGATIVE) {
            return false;
        }

        if (sign_value == BigInteger::Sign::ZERO && number.sign_value == BigInteger::Sign::POSITIVE) {
            return false;
        }
    } else {
        if (number.sign_value == BigInteger::Sign::POSITIVE) {
            if (number.value.size() > value.size()) {
                return false;
            } else {
                if (number.value.size() < value.size()) {
                    return true;
                }
            }

            for (size_t i = number.value.size() - 1; i != -1; --i) {
                if (number.value[i] > value[i]) {
                    return false;
                }
            }
        } else {
            if (number.sign_value == BigInteger::Sign::NEGATIVE) {
                if (number.value.size() < value.size()) {
                    return false;
                } else {
                    if (number.value.size() > value.size()) {
                        return true;
                    }
                }

                for (size_t i = number.value.size() - 1; i != -1; --i) {
                    if (number.value[i] < value[i]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

BigInteger& BigInteger::operator+=(const BigInteger& number)
{
    if (number.sign_value == BigInteger::Sign::ZERO) {
        return *this;
    }

    if (sign_value == BigInteger::Sign::ZERO) {
        *this = number;
        return *this;
    }

    if (sign_value == number.sign_value) {
        abs_sum(number);
    } else {
        BigInteger abs_this_big_int(BigInteger::Sign::POSITIVE, value);
        if (!abs_this_big_int.is_greater_than(BigInteger(BigInteger::Sign::POSITIVE, number.value))) {
            sign_value = number.sign_value;
        }
        abs_sub(number);
    }
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& number)
{
    if (number.sign_value == BigInteger::Sign::ZERO) {
        return *this;
    }

    if (sign_value == BigInteger::Sign::ZERO) {
        *this = number;
        if (number.sign_value == BigInteger::Sign::POSITIVE) {
            sign_value = BigInteger::Sign::NEGATIVE;
        } else {
            if (number.sign_value == BigInteger::Sign::NEGATIVE) {
                sign_value = BigInteger::Sign::POSITIVE;
            }
        }
        return *this;
    }

    if (sign_value == number.sign_value) {
        abs_sub(number);
    } else {
        BigInteger abs_this_big_int(BigInteger::Sign::POSITIVE, value);
        if (!abs_this_big_int.is_greater_than(BigInteger(BigInteger::Sign::POSITIVE, number.value))) {
            sign_value = number.sign_value;
        }
        abs_sum(number);
    }
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& number)
{
    if (number.sign_value == BigInteger::Sign::ZERO || sign_value == BigInteger::Sign::ZERO) {
        return *this;
    }

    sign_value = number.sign_value != sign_value ? BigInteger::Sign::NEGATIVE : BigInteger::Sign::POSITIVE;

    std::vector<uint32_t> res(number.value.size() + value.size() - 1, 0);
    for (size_t i = 0; i < number.value.size(); ++i) {
        int32_t carry = 0;
        for (size_t j = 0; j < value.size(); ++j) {
            uint32_t temp = res[i + j] + number.value[i] * value[j] + carry;
            res[i + j] = temp % BASE;
            carry = temp / BASE;
        }

        size_t m = value.size();
        while (carry) {
            res[m + i] = carry % BASE;
            carry /= BASE;
            ++m;
        }
    }

    value = res;
    return *this;
}

BigInteger operator*(const BigInteger& number_1, const BigInteger& number_2)
{
    BigInteger new_number = number_1;
    new_number *= number_2;
    return new_number;
}

BigInteger& BigInteger::operator=(const BigInteger& number)
{
    if (this == &number) {
        return *this;
    }
    this->value = number.value;
    this->sign_value = number.sign_value;
}

BigInteger& BigInteger::operator++()
{
    return *this += BigInteger(1);
}

BigInteger BigInteger::operator++(int)
{
    BigInteger new_big_int = *this;
    ++new_big_int;
    return new_big_int;
}

BigInteger& BigInteger::operator--()
{
    return *this -= BigInteger(1);
}

BigInteger BigInteger::operator--(int)
{
    BigInteger new_big_int = *this;
    --new_big_int;
    return new_big_int;
}

bool BigInteger::is_equal(const BigInteger& number) const
{
    if (sign_value == number.sign_value && value == number.value) {
        return true;
    }
    return false;
}

bool operator==(const BigInteger& number_1, const BigInteger& number_2)
{
    return number_1.is_equal(number_2);
}

bool operator!=(const BigInteger& number_1, const BigInteger& number_2)
{
    return !(number_1 == number_2);
}

bool operator>(const BigInteger& number_1, const BigInteger& number_2)
{
    return number_1.is_greater_than(number_2);
}

bool operator>=(const BigInteger& number_1, const BigInteger& number_2)
{
    return number_1 > number_2 || number_1 == number_2;
}

bool operator<(const BigInteger& number_1, const BigInteger& number_2)
{
    return !(number_1 >= number_2);
}

bool operator<=(const BigInteger& number_1, const BigInteger& number_2)
{
    return !(number_1 > number_2);
}

BigInteger& BigInteger::operator/=(const BigInteger& number)
{
    if (sign_value == BigInteger::Sign::ZERO) {
        return *this;
    }

    if (number.sign_value == BigInteger::Sign::ZERO) {
        throw DivisionByZero();
    }

    if (number.value.size() >= value.size()) {
        *this = BigInteger();
        return *this;
    }

    sign_value = number.sign_value != sign_value ? BigInteger::Sign::NEGATIVE : BigInteger::Sign::POSITIVE;

    std::vector<uint32_t> res(number.value.size() - value.size() + 1, 0);
    BigInteger res_del(sign_value, res);
    for (size_t i = res.size() - 1; i > 0; --i) {
        while (number * res_del <= *this) {
            ++res_del.value[i];
        }
    }

    value = res_del.value;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& number)
{
    BigInteger temp = *this;
    temp /= number;
    temp *= number;
    return *this -= temp;
}

BigInteger operator+(const BigInteger& number_1, const BigInteger& number_2)
{
    BigInteger new_number = number_1;
    new_number += number_2;
    return new_number;
}

BigInteger operator-(const BigInteger& number_1, const BigInteger& number_2)
{
    BigInteger new_number = number_1;
    new_number -= number_2;
    return new_number;
}

BigInteger operator/(const BigInteger& number_1, const BigInteger& number_2)
{
    BigInteger new_number = number_1;
    new_number /= number_2;
    return new_number;
}

BigInteger operator%(const BigInteger& number_1, const BigInteger& number_2){
    BigInteger new_number = number_1;
    new_number %= number_2;
    return new_number;
}

std::string BigInteger::toString() const
{
    std::ostringstream out;

    if (sign_value == BigInteger::Sign::ZERO) {
        out << 0;
        return out.str();
    }

    if (sign_value == BigInteger::Sign::NEGATIVE) {
        out << "-";
    }

    out << value.back();
    for (size_t i = value.size() - 1; i > 0; --i) {
        out << std::setw(CHANKSIZE) << std::setfill('0') << value[i - 1];
    }

    return out.str();
}

BigInteger::operator int() const
{
    if (sign_value == BigInteger::Sign::ZERO) {
        return 0;
    }

    if (value.size() > 1){
        throw UnsupportedValue();
    }
    int number;
    number = value[1];
    if(sign_value == BigInteger::Sign::ZERO){
        return number*= -1;
    }
}

BigInteger::operator bool() const{
    return sign_value == BigInteger::Sign::ZERO;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &number)
{
    out << number.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &number)
{
    std::string buffer;
    in >> buffer;

    number = BigInteger(buffer);
    return in;
}