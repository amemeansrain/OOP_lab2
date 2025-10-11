#include <string>
#include <stdexcept>

class Hex {
    private:
        unsigned char* data;
        size_t length;

        void allocate(size_t newLength);
        void deallocate();

        unsigned char charToDigit(char c) const;
        char digitToChar(unsigned char digit) const;
        void removeLeadingZeros();
        bool isValidHexChar(char c) const;

    public:
        Hex();
        Hex(const size_t& n, unsigned char t = 0);
        Hex(const std::string& t);
        Hex(const Hex& other);
        Hex(Hex&& other) noexcept;
        virtual ~Hex() noexcept;

        size_t size() const;
        std::string toString() const;

        Hex add(const Hex& other) const;
        Hex sub(const Hex& other) const;
        Hex copy() const;

        bool gt(const Hex& other) const;
        bool lt(const Hex& other) const;
        bool eq(const Hex& other) const;
};