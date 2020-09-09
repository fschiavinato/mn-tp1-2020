#pragma once 
#include<vector>
#include<ostream>
#include"../macros.h"

template<class T>
class vect: public std::vector<T> {
    public:
    vect(const int& n): std::vector<T>(n) {}
    friend std::ostream& operator<<(std::ostream& out, vect<T>& A) {
        out << "[";
        forn(i, A.size()) {
            out << A[i] << (i < A.size()-1? ", ": "");
        }
        out << "]";
        return out;
    }
};