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
    bool isNegative = false; // sign: true - "-", false - "+"
    std::vector<uint32_t> number;
    static const int ZERO = 0;
    bool checkTheValueContainsOnlyDigit(const std::string &value);
    void separationIntoSignedAndNumericPartsAndDefinitionSign(std::string &value, bool &isNegative);

public:
    BigInteger() : number{ZERO} {}      // constructor initializes zero
    BigInteger(const char* value);
    BigInteger(const int32_t& value); // if the number is within the range int32_t.
};