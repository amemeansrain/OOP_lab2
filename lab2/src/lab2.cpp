#include "../include/lab2.h"
#include <algorithm>
#include <cctype>

void Hex::allocate(size_t newLength) {
    if (newLength == 0) {
        data = nullptr;
        length = 0;
        return;
    }
    data = new unsigned char[newLength];
    length = newLength;
}

void Hex::deallocate() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    length = 0;
}

Hex::Hex() : data(nullptr), length(0) {
    allocate(1);
    data[0] = 0;
}

Hex::Hex(const size_t& n, unsigned char t) : data(nullptr), length(0) {
    if (n == 0) {
        throw std::invalid_argument("Size cannot be zero");
    }
    if (t > 15) {
        throw std::invalid_argument("Digit must be between 0 and 15");
    }
    allocate(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = t;
    }
    removeLeadingZeros();
}

Hex::Hex(const std::string& t) : data(nullptr), length(0) {
    if (t.empty()) {
        allocate(1);
        data[0] = 0;
        return;
    }
    for (char c : t) {
        if (!isValidHexChar(c)) {
            throw std::invalid_argument("Invalid hex character");
        }
    }
    allocate(t.length());
    for (size_t i = 0; i < t.length(); ++i) {
        data[i] = charToDigit(t[i]);
    }
    removeLeadingZeros();
}

Hex::Hex(const Hex& other) : data(nullptr), length(0) {
    if (other.length > 0) {
        allocate(other.length);
        for (size_t i = 0; i < other.length; ++i) {
            data[i] = other.data[i];
        }
    }
}

Hex::Hex(Hex&& other) noexcept 
    : data(other.data), length(other.length) {
    other.data = nullptr;
    other.length = 0;
}

Hex::~Hex() noexcept {
    deallocate();
}

unsigned char Hex::charToDigit(char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    throw std::invalid_argument("Invalid hex character");
}

char Hex::digitToChar(unsigned char digit) const {
    if (digit < 10) return '0' + digit;
    return 'A' + (digit - 10);
}

bool Hex::isValidHexChar(char c) const {
    return (c >= '0' && c <= '9') || 
           (c >= 'A' && c <= 'F') || 
           (c >= 'a' && c <= 'f');
}

void Hex::removeLeadingZeros() {
    if (length == 0) return;
    size_t firstNonZero = 0;
    while (firstNonZero < length - 1 && data[firstNonZero] == 0) {
        firstNonZero++;
    }
    if (firstNonZero > 0) {
        size_t newLength = length - firstNonZero;
        unsigned char* newData = new unsigned char[newLength];
        for (size_t i = 0; i < newLength; ++i) {
            newData[i] = data[firstNonZero + i];
        }
        deallocate();
        data = newData;
        length = newLength;
    }
}

size_t Hex::size() const {
    return length;
}

std::string Hex::toString() const {
    std::string result;
    for (size_t i = 0; i < length; ++i) {
        result += digitToChar(data[i]);
    }
    return result;
}

Hex Hex::add(const Hex& other) const {
    size_t maxSize = std::max(length, other.length);
    size_t resultSize = maxSize + 1;
    Hex result;
    result.allocate(resultSize);
    for (size_t i = 0; i < resultSize; ++i) {
        result.data[i] = 0;
    }
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char sum = carry;
        if (i < length) sum += data[length - 1 - i];
        if (i < other.length) sum += other.data[other.length - 1 - i];
        result.data[resultSize - 1 - i] = sum % 16;
        carry = sum / 16;
    }
    result.removeLeadingZeros();
    return result;
}

Hex Hex::sub(const Hex& other) const {
    if (this->lt(other)) {
        throw std::invalid_argument("Cannot subtract larger number from smaller");
    }
    Hex result;
    result.allocate(length);
    for (size_t i = 0; i < length; ++i) {
        result.data[i] = 0;
    }
    int borrow = 0;
    for (size_t i = 0; i < length; ++i) {
        int digitA = data[length - 1 - i];
        int digitB = (i < other.length) ? other.data[other.length - 1 - i] : 0;
        digitA -= borrow;
        if (digitA < digitB) {
            digitA += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.data[length - 1 - i] = digitA - digitB;
    }
    result.removeLeadingZeros();
    return result;
}

Hex Hex::copy() const {
    return Hex(*this);
}

bool Hex::gt(const Hex& other) const {
    if (length != other.length) {
        return length > other.length;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return data[i] > other.data[i];
        }
    }
    return false;
}

bool Hex::lt(const Hex& other) const {
    if (length != other.length) {
        return length < other.length;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return data[i] < other.data[i];
        }
    }
    return false;
}

bool Hex::eq(const Hex& other) const {
    if (length != other.length) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}