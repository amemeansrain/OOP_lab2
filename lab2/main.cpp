#include <iostream>
#include "include/lab2.h"

int main() {
    Hex num1("1A3F");
    Hex num2("B2C");
    
    std::cout << "num1: " << num1.toString() << std::endl;
    std::cout << "num2: " << num2.toString() << std::endl;
    
    Hex sum = num1.add(num2);
    Hex diff = num1.sub(num2);
    
    std::cout << "1A3F + B2C = " << sum.toString() << std::endl;
    std::cout << "1A3F - B2C = " << diff.toString() << std::endl;
    std::cout << "1A3F > B2C: " << num1.gt(num2) << std::endl;
    std::cout << "1A3F < B2C: " << num1.lt(num2) << std::endl;
    std::cout << "1A3F == 1A3F: " << num1.eq(num1) << std::endl;
    
    return 0;
}