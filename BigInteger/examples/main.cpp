#include <bigInt.hpp>
#include <iostream>

int main()
{
    BigInteger A;
    BigInteger B(std::string("10000"));
    BigInteger C(130);
    C/=B ;

    std::cout << C.toString() << '\n';
    return 0;
}