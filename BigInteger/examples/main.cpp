#include <bigInt.hpp>
#include <iostream>

int main()
{
    BigInteger A();
    BigInteger B(std::string("100010232100853342"));
    BigInteger C(123241532);

    std::cout << B.toString() << '\n';
    return 0;
}