#include <string>
#include <stdexcept>

class Hex {
private:
    unsigned char* digits;
    size_t size;

    void allocateMemory(size_t newSize);
    void freeMemory();
    
    unsigned char convertCharToDigit(char c) const;
    char convertDigitToChar(unsigned char digit) const;
    void trimLeadingZeros();
    bool isValidHexCharacter(char c) const;

public:
    Hex();
    Hex(const size_t& size, unsigned char value = 0);
    Hex(const std::string& hexString);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    ~Hex() noexcept;

    size_t getSize() const;
    std::string toString() const;

    Hex add(const Hex& other) const;
    Hex subtract(const Hex& other) const;
    Hex createCopy() const;

    bool isGreater(const Hex& other) const;
    bool isLess(const Hex& other) const;
    bool isEqual(const Hex& other) const;
};