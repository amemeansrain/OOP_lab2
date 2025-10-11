#include <iostream>
#include "include/lab2.h"

int main() {
    try {
        Hex a("1A3F");
        Hex b("B2C");
        
        std::cout << "a: " << a.toStr() << std::endl;
        std::cout << "b: " << b.toStr() << std::endl;
        
        Hex c = a.plus(b);
        Hex d = a.minus(b);
        
        std::cout << "a+b: " << c.toStr() << std::endl;
        std::cout << "a-b: " << d.toStr() << std::endl;
        
        std::cout << "a>b: " << a.more(b) << std::endl;
        std::cout << "a<b: " << a.less(b) << std::endl;
        std::cout << "a==a: " << a.same(a) << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}