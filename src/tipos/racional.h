#pragma once
#include<ostream>
using namespace std;

class racional {
private:
    long long num;
    long long den;

    long long mcm(long long num, long long den) {
        while(den != 0) {
            long long resto = num % den;
            num = den;
            den = resto;
        }
        return num;
    }
public:
    racional(long long n): num(n), den(1) {};
    racional(long long _num, long long _den) {
        long long _mcm = mcm(_num, _den);
        num = _num / _mcm;
        den = _den / _mcm;
    };
    racional(): num(0), den(1) {};
    racional operator+(const racional &b) const {
        return racional(num*b.den+b.num*den, den*b.den);
    };
    racional operator-() const {
        return racional(-num, den);
    };
    racional operator-(const racional &b) { 
        return *this + (-b);
       };
    racional operator*(const racional &b) const {
        return racional(num*b.num, den*b.den);
    };
    racional operator/(const racional &b) const {
        return racional(num*b.den, den*b.num);
    };
    racional &operator=(const racional &b) {
        num = b.num;
        den = b.den;
        return *this;
    };
    racional &operator-=(const racional &b) { return *this = *this - b; };
    racional &operator+=(const racional &b) { return *this = *this + b; };
    racional &operator++(int) { return *this += 1; };
    friend ostream &operator<<(ostream &out, const racional &b) {
        out << float(b.num) / b.den;
        return out;
    }
};