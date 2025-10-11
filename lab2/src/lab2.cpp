#include "../include/lab2.h"
#include <algorithm>
#include <cctype>

void Hex::allocateMemory(size_t newSize) {
    if (newSize == 0) {
        digits = nullptr;
        size = 0;
        return;
    }
    digits = new unsigned char[newSize];
    size = newSize;
}

void Hex::freeMemory() {
    if (digits != nullptr) {
        delete[] digits;
        digits = nullptr;
    }
    size = 0;
}

Hex::Hex() : digits(nullptr), size(0) {
    allocateMemory(1);
    digits[0] = 0;
}

Hex::Hex(const size_t& arraySize, unsigned char value) : digits(nullptr), size(0) {
    if (arraySize == 0) {
        throw std::invalid_argument("Array size must be greater than zero");
    }
    if (value > 15) {
        throw std::invalid_argument("Hex digit must be between 0 and 15");
    }
    
    allocateMemory(arraySize);
    for (size_t i = 0; i < arraySize; i++) {
        digits[i] = value;
    }
    trimLeadingZeros();
}

Hex::Hex(const std::string& hexString) : digits(nullptr), size(0) {
    if (hexString.empty()) {
        allocateMemory(1);
        digits[0] = 0;
        return;
    }
    
    for (char character : hexString) {
        if (!isValidHexCharacter(character)) {
            throw std::invalid_argument("String contains invalid hex characters");
        }
    }
    
    allocateMemory(hexString.length());
    
    for (size_t i = 0; i < hexString.length(); i++) {
        digits[i] = convertCharToDigit(hexString[i]);
    }
    
    trimLeadingZeros();
}

Hex::Hex(const Hex& other) : digits(nullptr), size(0) {
    if (other.size > 0) {
        allocateMemory(other.size);
        for (size_t i = 0; i < other.size; i++) {
            digits[i] = other.digits[i];
        }
    }
}

Hex::Hex(Hex&& other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

Hex::~Hex() noexcept {
    freeMemory();
}

unsigned char Hex::convertCharToDigit(char c) const {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    throw std::invalid_argument("Invalid hex character");
}

char Hex::convertDigitToChar(unsigned char digit) const {
    if (digit < 10) {
        return '0' + digit;
    }
    return 'A' + (digit - 10);
}

bool Hex::isValidHexCharacter(char c) const {
    return (c >= '0' && c <= '9') || 
           (c >= 'A' && c <= 'F') || 
           (c >= 'a' && c <= 'f');
}

void Hex::trimLeadingZeros() {
    if (size == 0) return;
    
    size_t firstSignificantDigit = 0;
    while (firstSignificantDigit < size - 1 && digits[firstSignificantDigit] == 0) {
        firstSignificantDigit++;
    }
    
    if (firstSignificantDigit > 0) {
        size_t newSize = size - firstSignificantDigit;
        unsigned char* newDigits = new unsigned char[newSize];
        
        for (size_t i = 0; i < newSize; i++) {
            newDigits[i] = digits[firstSignificantDigit + i];
        }
        
        freeMemory();
        digits = newDigits;
        size = newSize;
    }
}

size_t Hex::getSize() const {
    return size;
}

std::string Hex::toString() const {
    std::string result;
    for (size_t i = 0; i < size; i++) {
        result += convertDigitToChar(digits[i]);
    }
    return result;
}

Hex Hex::add(const Hex& other) const {
    size_t maxLength = std::max(size, other.size);
    size_t resultLength = maxLength + 1;
    
    Hex result;
    result.allocateMemory(resultLength);
    
    for (size_t i = 0; i < resultLength; i++) {
        result.digits[i] = 0;
    }
    
    unsigned char carry = 0;
    
    for (size_t i = 0; i < maxLength || carry > 0; i++) {
        unsigned char sum = carry;
        
        if (i < size) {
            sum += digits[size - 1 - i];
        }
        if (i < other.size) {
            sum += other.digits[other.size - 1 - i];
        }
        
        result.digits[resultLength - 1 - i] = sum % 16;
        carry = sum / 16;
    }
    
    result.trimLeadingZeros();
    return result;
}

Hex Hex::subtract(const Hex& other) const {
    if (isLess(other)) {
        throw std::invalid_argument("Cannot subtract larger number from smaller");
    }
    
    Hex result;
    result.allocateMemory(size);
    
    for (size_t i = 0; i < size; i++) {
        result.digits[i] = 0;
    }
    
    int borrow = 0;
    
    for (size_t i = 0; i < size; i++) {
        int currentDigit = digits[size - 1 - i];
        int otherDigit = (i < other.size) ? other.digits[other.size - 1 - i] : 0;
        
        currentDigit -= borrow;
        
        if (currentDigit < otherDigit) {
            currentDigit += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.digits[size - 1 - i] = currentDigit - otherDigit;
    }
    
    result.trimLeadingZeros();
    return result;
}

Hex Hex::createCopy() const {
    return Hex(*this);
}

bool Hex::isGreater(const Hex& other) const {
    if (size != other.size) {
        return size > other.size;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
        }
    }
    
    return false;
}

bool Hex::isLess(const Hex& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    
    return false;
}

bool Hex::isEqual(const Hex& other) const {
    if (size != other.size) {
        return false;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    
    return true;
}