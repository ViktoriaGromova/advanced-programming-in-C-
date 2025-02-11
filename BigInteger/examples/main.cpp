#include <bigInt.hpp>
#include <iostream>

int main()
{
    BigInteger A;
    BigInteger B(std::string("100010232100853342"));
    BigInteger C(-12324132);
    C-=B ;

    std::cout << C.toString() << '\n';
    return 0;
}