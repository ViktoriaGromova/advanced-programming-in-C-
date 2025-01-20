#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ostream>
#include <string>
#include <vector>

constexpr int32_t BASE = 1e9;
constexpr int8_t CHANKSSIZE = 9;

class BigInteger {
public:
    enum class Sign;

    explicit BigInteger();
    BigInteger(const int32_t& number);
    BigInteger(const std::string& number);
    // explicit BigInteger(bool isNegative, std::vector<uint32_t> number);

private:
    Sign sign_value;
    std::vector<uint32_t> number;

    Sign sign(int32_t value);
};