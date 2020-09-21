#pragma once 
#include<vector>
#include <initializer_list>
#include<ostream>
#include"../macros.h"

template<class T>
class vect: public std::vector<T> {
    public:
    vect(): std::vector<T>() {}
    vect(const int& n): std::vector<T>(n) {}
    vect(std::initializer_list<T> a): std::vector<T>(a) {}
    vect(const int& n, T val): std::vector<T>(n, val) {}
    friend std::ostream& operator<<(std::ostream& out, vect<T>& A) {
        if(&out == &clog){
            out << "[";
            forn(i, A.size()) {
                out << A[i] << (i < A.size()-1? ", ": "");
            }
            out << "]" << endl;
        } else {
            forn(i, A.size()) {
                out << A[i] << endl;
            }
        }
        return out;
    }
};