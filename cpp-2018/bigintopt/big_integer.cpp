#include "big_integer.h"

#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iostream>

typedef unsigned long long ULL;
typedef unsigned int UI;

ULL BASE = 4294967296ULL; //2^32

void big_integer::fit() {
    while (length() > 0 && digits.back() == 0) {
        digits.pop_back();
    }
    if (length() == 0) {
        sign = false;
    }
}

void big_integer::two_comp(size_t s) {
    while (digits.size() != s) {
        digits.push_back(0);
    }
    if (!sign) {
        return;
    }
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] = ~digits[i];
    }
    add_long_short(1);
}

int cmp(big_integer const& a, big_integer const& b) {
    if (a.sign != b.sign) {
        return (a.sign ? -1 : 1);
    } else {
        int temp = cmpl(a, b);
        if (a.sign) {
            return -temp;
        } else {
            return temp;
        }
    }
}

int cmpl(big_integer const& a, big_integer const& b) {
    if (a.length() != b.length()) {
        if (a.length() > b.length()) {
            return 1;
        } else {
            return -1;
        }
    }
    for (size_t i = a.length(); i > 0; i--) {
        if (a.getDigit(i - 1) < b.getDigit(i - 1)) {
            return -1;
        } else if (a.getDigit(i - 1) > b.getDigit(i - 1)) {
            return 1;
        }
    }
    return 0;
}

void big_integer::mul_long_short(UI b) {
    ULL carry = 0;
    for (size_t i = 0; i < length() || carry; ++i) {
        if (i == length()) {
            digits.push_back(0);
        }
        ULL temp = carry + (ULL)b * digits[i];
        digits[i] = temp % BASE;
        carry = temp / BASE;
    }
    fit();
}

void big_integer::div_long_short(UI b) {
    ULL carry = 0;
    for (size_t i = length(); i > 0; --i) {
        ULL temp = digits[i - 1] + carry * BASE;
        digits[i - 1] = temp / b;
        carry = temp % b;
    }
    fit();
}

void big_integer::add_long_short(UI b) {
    ULL carry = b;
    for (size_t i = 0; i < length() || carry; ++i) {
        if (i == length()) {
            digits.push_back(0);
        }
        ULL temp = carry + digits[i];
        digits[i] = temp % BASE;
        carry = temp / BASE;
    }
    fit();
}

void big_integer::mul_long_long(big_integer const& other) {
    big_integer c;
    c.digits.resize(length() + other.length() + 1);
    for (size_t i = 0; i < length(); ++i) {
        ULL carry = 0;
        for (size_t j = 0; j < other.length() || carry; ++j) {
            ULL temp = (ULL)c.getDigit(i + j) + (ULL)getDigit(i) * (j < other.length() ? other.getDigit(j) : 0) + carry;
            c.digits[i + j] = temp % BASE;
            carry = temp / BASE;
        }
    }
    c.fit();
    digits = c.digits;
    //fit();
}

void big_integer::add_long_long(big_integer const& other) {
    ULL carry = 0;
    for (size_t i = 0; i < std::max(length(), other.length()) || carry; ++i) {
        if (i == length()) {
            digits.push_back(0);
        }
        ULL temp = carry + digits[i] + (i < other.length() ? other.getDigit(i) : 0);
        digits[i] = temp % BASE;
        carry = temp / BASE;
    }
    fit();
}

void big_integer::sub_long_long(big_integer const& other) {
    ULL carry = 0;
    for (size_t i = 0; i < other.length() || carry; ++i) {
        ULL temp = carry + (i < other.length() ? other.getDigit(i) : 0);
        if (digits[i] >= temp) {
            digits[i] -= temp;
            carry = 0;
        } else {
            digits[i] -= temp - BASE;
            carry = 1;
        }
    }
    fit();
}

UI get_t(const UI a, const UI b, const UI c) {
    ULL res = a;
    res = ((res << 32) + b) / c;
    if (res > BASE) {
        res = BASE;
    }
    return res;
}

void big_integer::div_long_long(big_integer const& other) {
    if (other.length() == 0) {
        throw std::runtime_error("Division by zero");
    }
    if (other.length() == 1) {
        div_long_short(other.digits.back());
        return;
    }
    if (cmpl(*this, other) < 0) {
        digits.clear();
        sign = false;
        return;
    }
    big_integer temp = other;
    size_t n = length(), m = temp.length();
    size_t len = n - m + 1;
    if (temp.digits.back() < BASE/2) {
        UI d = (BASE + 1ULL) / (temp.digits.back() + 1ULL);
        mul_long_short(d);
        temp.mul_long_short(d);
    }

    big_integer q;
    big_integer b;
    big_integer a;
    q.digits.resize(len);
    a.digits.resize(m + 1);
    b.digits.resize(m + 1);
    UI divisor = temp.digits.back();
    for (size_t i = 0; i < m; ++i) {
        a.digits[i] = digits[n + i - m];
    }
    if (n < length()) {
        a.digits[m] = digits[n];
    }

    for (size_t i = 0; i < len; ++i) {
        a.digits[0] = digits[n - m - i];
        UI tempq = get_t(a.digits[m], a.digits[m - 1], divisor);
        b = temp;
        b.mul_long_short(tempq);
        while ((tempq >= 0) && (cmpl(a, b) < 0)) {
            b = temp;
            b.mul_long_short(--tempq);
        }
        a.sub_long_long(b);
        a.digits.resize(m + 1);
        for (size_t j = m; j > 0; --j) {
            a.digits[j] = a.digits[j - 1];
        }
        q.digits[len - 1 - i] = tempq;
    }
    digits = q.digits;
}

size_t big_integer::length() const {
    return digits.size();
}

big_integer::big_integer() {
    sign = false;
}

big_integer::big_integer(big_integer const& other) {
    digits = other.digits;
    sign = other.sign;
}

big_integer::big_integer(int a) {
    sign = false;
    if (a < 0) {
        sign = true;
        digits.push_back(-(unsigned)a);
    } else if (a > 0) {
        digits.push_back(a);
    }
}

big_integer::big_integer(std::string const& str) {
    digits.push_back(0);
    sign = false;
    for (size_t i = 0; i < str.length(); i++) {
        if (i == 0 && str[i] == '-') {
            sign = true;
            continue;
        }
        if (!(str[i] >= '0' && str[i] <= '9')) {
            throw std::runtime_error("invalid string");
        }
        add_long_short(str[i] - '0');
        mul_long_short(10);
    }
    div_long_short(10);
    fit();
}

big_integer::~big_integer() {
    //digits.clear();
}

big_integer& big_integer::operator=(big_integer const& other) {
    this->digits = other.digits;
    this->sign = other.sign;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& other) {
    if (!sign && !other.sign) {
        this->add_long_long(other);
    } else if (!sign && other.sign) {
        if (cmpl(*this, other) >= 0) {
            this->sub_long_long(other);
        } else {
            big_integer temp(other);
            temp.sub_long_long(*this);
            this->digits = temp.digits;
            this->sign = true;
        }
    } else if (sign && !other.sign) {
        if (cmpl(other, *this) >= 0) {
            big_integer temp(other);
            temp.sub_long_long(*this);
            this->digits = temp.digits;
            this->sign = false;
        } else {
            this->sub_long_long(other);
            this->sign = true;
        }
    } else {
        this->add_long_long(other);
        this->sign = true;
    }
    fit();
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& other) {
    big_integer temp(other);
    temp.sign = !temp.sign;
    *this += temp;
    return *this;
}

big_integer& big_integer::operator*=(big_integer const& other) {
    this->mul_long_long(other);
    this->sign ^= other.sign;
    return *this;
}

big_integer& big_integer::operator/=(big_integer const& other) {
    div_long_long(other);
    sign ^= other.sign;
    fit();
    return *this;
}

big_integer& big_integer::operator%=(big_integer const& other) {
    *this = *this - (*this / other) * other;
    return *this;
}

big_integer& big_integer::operator&=(big_integer const& other) {
    size_t t = std::max(digits.size(), other.digits.size()) + 1;
    big_integer temp(other);
    two_comp(t);
    temp.two_comp(t);
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] &= temp.digits[i];
    }
    if (digits.back() >= BASE / 2) {
        sign = true;
    } else {
        sign = false;
    }
    two_comp(digits.size());
    fit();
    return *this;
}

big_integer& big_integer::operator|=(big_integer const& other) {
    size_t t = std::max(digits.size(), other.digits.size()) + 1;
    big_integer temp(other);
    two_comp(t);
    temp.two_comp(t);
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] |= temp.digits[i];
    }
    if (digits.back() >= BASE / 2) {
        sign = true;
    } else {
        sign = false;
    }
    two_comp(digits.size());
    fit();
    return *this;
}

big_integer& big_integer::operator^=(big_integer const& other) {
    size_t t = std::max(digits.size(), other.digits.size()) + 1;
    big_integer temp(other);
    two_comp(t);
    temp.two_comp(t);
    for (size_t i = 0; i < digits.size(); ++i) {
        digits[i] ^= temp.digits[i];
    }
    if (digits.back() >= BASE / 2) {
        sign = true;
    } else {
        sign = false;
    }
    two_comp(digits.size());
    fit();
    return *this;
}

big_integer& big_integer::operator<<=(int b) {
    if (b == 0) {
        return *this;
    }
    UI div = b / 32;
    UI mod = b % 32;
    big_integer temp;
    temp.digits.resize(length() + div);
    temp.digits[div] = (digits[0] << mod);
    for (size_t i = div + 1; i < temp.length(); ++i) {
        ULL x = digits[i - div];
        x <<= mod;
        ULL y = digits[i - div - 1];
        y >>= (32 - mod);
        temp.digits[i] = x + y;
    }
    temp.fit();
    this->digits = temp.digits;
    return *this;
}

big_integer& big_integer::operator>>=(int b) {
    if (b == 0) {
        return *this;
    }
    two_comp(length() + 1);
    UI div = b / 32;
    UI mod = b % 32;
    big_integer temp;
    if (div < length()) {
        temp.digits.resize(length() - div - 1);
    }
    for (size_t i = 0; i < temp.length(); ++i) {
        ULL x = digits[i + div];
        x >>= mod;
        ULL y = digits[i + div + 1];
        y <<= (32 - mod);
        temp.digits[i] = x + y;
    }
    temp.fit();
    this->digits = temp.digits;
    two_comp(length());
    return *this;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    big_integer r(*this);
    r.sign = !r.sign;
    r.fit();
    return r;
}

big_integer big_integer::operator~() const {
    big_integer temp(*this);
    temp.two_comp(temp.digits.size() + 1);
    for (size_t i = 0; i < temp.digits.size(); ++i) {
        temp.digits[i] = ~temp.digits[i];
    }
    if (temp.digits.back() >= BASE / 2) {
        temp.sign = true;
    } else {
        temp.sign = false;
    }
    temp.two_comp(temp.digits.size());
    temp.fit();
    return temp;
}

big_integer& big_integer::operator++() {
    //add_long_short(1);
    return *this;
}

big_integer big_integer::operator++(int t) {
    //add_long_short(t);
    return *this;
}

big_integer& big_integer::operator--() {
    //nothing
    return *this;
}

big_integer big_integer::operator--(int) {
    //nothing
    return *this;
}

big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const& b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const& b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}

bool operator==(big_integer const& a, big_integer const& b) {
    return cmp(a, b) == 0;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return cmp(a, b) != 0;
}

bool operator<(big_integer const& a, big_integer const& b) {
    return cmp(a, b) < 0;
}

bool operator>(big_integer const& a, big_integer const& b) {
    return cmp(a, b) > 0;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return cmp(a, b) <= 0;
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return cmp(a, b) >= 0;
}

std::string to_string(big_integer const& a) {
    big_integer cur = a;
    if (cur.length() == 0) {
        return "0";
    }
    std::string res = "";
    while (cur.length() != 0) {
        ULL ans = cur.getDigit(0) % 10;
        for (size_t i = 1; i < cur.length(); i++) {
            ans = (ans + ((cur.getDigit(i) % 10) * 6) % 10) % 10;
        }
        res += (ans + '0');
        cur.div_long_short(10);
    }
    if (a.sign) {
        res += '-';
    }
    reverse(res.begin(), res.end());
    return res;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a) {
    return s << to_string(a);
}

UI big_integer::getDigit(int i) const {
    return digits[i];
}
