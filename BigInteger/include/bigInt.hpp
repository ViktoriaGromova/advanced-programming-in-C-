#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ostream>
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
    
    BigInteger& operator +=(const BigInteger& number);

private:
    Sign sign_value;
    std::vector<uint32_t> value;

    Sign sign(int32_t value) const;
    bool isNotZeroVector(const std::vector<uint32_t>& number) const;
};