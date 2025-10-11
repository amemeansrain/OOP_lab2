#include <iostream>
#include "lab2.h"

int main() {
    try {
        Hex number1("1A3F");
        Hex number2("B2C");
        
        std::cout << "First number: " << number1.toString() << std::endl;
        std::cout << "Second number: " << number2.toString() << std::endl;
        
        Hex sum = number1.add(number2);
        Hex difference = number1.subtract(number2);
        
        std::cout << "Sum: " << sum.toString() << std::endl;
        std::cout << "Difference: " << difference.toString() << std::endl;
        
        std::cout << "First number is greater: " << (number1.isGreater(number2) ? "yes" : "no") << std::endl;
        std::cout << "First number is smaller: " << (number1.isLess(number2) ? "yes" : "no") << std::endl;
        std::cout << "Numbers are equal: " << (number1.isEqual(number2) ? "yes" : "no") << std::endl;
        
        Hex copy = number1.createCopy();
        std::cout << "Copy of first number: " << copy.toString() << std::endl;
        
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
    
    return 0;
}