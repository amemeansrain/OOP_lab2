#ifndef LAB2_H
#define LAB2_H

#include <string>
#include <stdexcept>

class Hex {
    private:
        unsigned char* data;
        size_t len;

        void alloc(size_t n);
        void del();

        unsigned char c2d(char c) const;
        char d2c(unsigned char d) const;
        void rm0();
        bool good(char c) const;

    public:
        Hex();
        Hex(const size_t& n, unsigned char t = 0);
        Hex(const std::string& s);
        Hex(const Hex& o);
        Hex(Hex&& o) noexcept;
        virtual ~Hex() noexcept;

        size_t size() const;
        std::string toStr() const;

        Hex plus(const Hex& o) const;
        Hex minus(const Hex& o) const;
        Hex dup() const;

        bool more(const Hex& o) const;
        bool less(const Hex& o) const;
        bool same(const Hex& o) const;
};

#endif