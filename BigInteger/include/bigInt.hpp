#pragma once

#include <vector>
#include <ostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <algorithm>

constexpr int32_t BASE = 1e9;
constexpr int8_t CHANKSSIZE = 9; 

class BigInteger
{
private:
    static const int ZERO = 0;

    bool isNegative = false; // sign: true - "-", false - "+"
    std::vector<uint32_t> number;

    bool checkTheValueContainsOnlyDigit(const std::string &value) const;
    std::string separationIntoSignedAndNumericPartsAndDefinitionSign(const std::string &value, bool &isNegative);
    BigInteger abs() const { return BigInteger(false, this->number);
}

public:
    BigInteger() : number{ZERO} {}      // constructor initializes zero
    explicit BigInteger(bool isNegative, std::vector<uint32_t> number);
    explicit BigInteger(const char* value);
    explicit BigInteger(const int32_t& value); // if the number is within the range int32_t.
};