#include "../include/lab2.h"
#include <iostream>
#include <algorithm>

void Hex::alloc(size_t n) {
    if (n == 0) {
        data = 0;
        len = 0;
        return;
    }
    data = new unsigned char[n];
    len = n;
}

void Hex::del() {
    if (data) {
        delete[] data;
        data = 0;
    }
    len = 0;
}

Hex::Hex() {
    data = 0;
    len = 0;
    alloc(1);
    data[0] = 0;
}

Hex::Hex(const size_t& n, unsigned char t) {
    data = 0;
    len = 0;
    if (n == 0) throw std::invalid_argument("bad size");
    if (t > 15) throw std::invalid_argument("bad digit");
    alloc(n);
    for (size_t i = 0; i < n; i++) data[i] = t;
    rm0();
}

Hex::Hex(const std::string& s) {
    data = 0;
    len = 0;
    if (s.empty()) {
        alloc(1);
        data[0] = 0;
        return;
    }
    for (char c : s) if (!good(c)) throw std::invalid_argument("bad char");
    alloc(s.length());
    for (size_t i = 0; i < s.length(); i++) data[i] = c2d(s[i]);
    rm0();
}

Hex::Hex(const Hex& o) {
    data = 0;
    len = 0;
    if (o.len > 0) {
        alloc(o.len);
        for (size_t i = 0; i < o.len; i++) data[i] = o.data[i];
    }
}

Hex::Hex(Hex&& o) noexcept {
    data = o.data;
    len = o.len;
    o.data = 0;
    o.len = 0;
}

Hex::~Hex() noexcept {
    del();
}

unsigned char Hex::c2d(char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    throw std::invalid_argument("bad char");
}

char Hex::d2c(unsigned char d) const {
    if (d < 10) return '0' + d;
    return 'A' + (d - 10);
}

bool Hex::good(char c) const {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

void Hex::rm0() {
    if (len == 0) return;
    size_t start = 0;
    while (start < len - 1 && data[start] == 0) start++;
    if (start > 0) {
        size_t new_len = len - start;
        unsigned char* new_data = new unsigned char[new_len];
        for (size_t i = 0; i < new_len; i++) new_data[i] = data[start + i];
        del();
        data = new_data;
        len = new_len;
    }
}

size_t Hex::size() const {
    return len;
}

std::string Hex::toStr() const {
    std::string res;
    for (size_t i = 0; i < len; i++) res += d2c(data[i]);
    return res;
}

Hex Hex::plus(const Hex& o) const {
    size_t max_len = std::max(len, o.len);
    size_t res_len = max_len + 1;
    Hex res;
    res.alloc(res_len);
    for (size_t i = 0; i < res_len; i++) res.data[i] = 0;
    unsigned char carry = 0;
    for (size_t i = 0; i < max_len || carry; i++) {
        unsigned char sum = carry;
        if (i < len) sum += data[len - 1 - i];
        if (i < o.len) sum += o.data[o.len - 1 - i];
        res.data[res_len - 1 - i] = sum % 16;
        carry = sum / 16;
    }
    res.rm0();
    return res;
}

Hex Hex::minus(const Hex& o) const {
    if (less(o)) throw std::invalid_argument("can't subtract");
    Hex res;
    res.alloc(len);
    for (size_t i = 0; i < len; i++) res.data[i] = 0;
    int borrow = 0;
    for (size_t i = 0; i < len; i++) {
        int a = data[len - 1 - i];
        int b = (i < o.len) ? o.data[o.len - 1 - i] : 0;
        a -= borrow;
        if (a < b) {
            a += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.data[len - 1 - i] = a - b;
    }
    res.rm0();
    return res;
}

Hex Hex::dup() const {
    return Hex(*this);
}

bool Hex::more(const Hex& o) const {
    if (len != o.len) return len > o.len;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != o.data[i]) return data[i] > o.data[i];
    }
    return false;
}

bool Hex::less(const Hex& o) const {
    if (len != o.len) return len < o.len;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != o.data[i]) return data[i] < o.data[i];
    }
    return false;
}

bool Hex::same(const Hex& o) const {
    if (len != o.len) return false;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != o.data[i]) return false;
    }
    return true;
}