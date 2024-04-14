#include <stdlib.h>
#include <iostream>
    union A
    {
        int a;
        char b;
    };
int main() {

    A test;
    test.a = 0x000000001;
    printf("b is %d\n", test.b);
    std::cout << "b is :" << test.b << std::endl;
    std::cout << "a is :" << test.a << std::endl;
}