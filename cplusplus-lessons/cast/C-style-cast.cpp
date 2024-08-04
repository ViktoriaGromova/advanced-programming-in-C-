#include<iostream>

int main(){ 
    // C-style cast - самый нежелательный каст, так как нельзя отследить ошибки;
    // Он объеденять все касты;
    // C указателями через interpret_cast;
    double d = 0.0;
    int x = (int) d;
    std::cout << "C-style cast x: " << std::endl;
    return 0;
}