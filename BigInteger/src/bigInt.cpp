#include "bigInt.hpp"
#include <string>
#include <iostream>

std::string BigInteger::separationIntoSignedAndNumericPartsAndDefinitionSign(const std::string &value, bool &isNegative)
{
    if (value[0] == '-' || value[0] == '+')
    {
        isNegative = (value[0] == '-');
        return value.substr(1);
    }
    return value;
}

bool BigInteger::checkTheValueContainsOnlyDigit(const std::string &value) const 
{
    return std::all_of(value.begin(), value.end(), ::isdigit);
}

BigInteger::BigInteger(const int32_t& value)
{
    if (value == 0)
        BigInteger();
    else
    {
        isNegative = value < 0;
        uint32_t absValue = std::abs(value);
        number.push_back(absValue);
    }
}

BigInteger::BigInteger(const char* val)
{
    std::string value = std::string(val);
    if (value.empty())
        BigInteger();

    separationIntoSignedAndNumericPartsAndDefinitionSign(value, isNegative);

    if (checkTheValueContainsOnlyDigit(value))
    {
        size_t i = value.size() - 1;
        while (i > 0)
        {
            int32_t chank = 0;
            if (i >= CHANKSSIZE)
            {
                chank = std::stoi(value.substr(i - CHANKSSIZE + 1, i));
                i -= CHANKSSIZE;
            }
            else
            {
                chank = std::stoi(value.substr(0, i));
                i = 0; // i -= i is 0
            }
            number.push_back(chank);
        }
    }
    else
        throw std::invalid_argument("The number was entered incorrectly");
}