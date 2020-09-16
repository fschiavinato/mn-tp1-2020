#pragma once 
#include<vector>
#include<ostream>
#include"../macros.h"

template<class T>
class vect: public std::vector<T> {
    public:
    vect(): std::vector<T>() {}
    vect(const int& n): std::vector<T>(n) {}
    friend std::ostream& operator<<(std::ostream& out, vect<T>& A) {
        if(out == stdout){
            out << "[";
            forn(i, A.size()) {
                out << A[i] << (i < A.size()-1? ", ": "");
            }
            out << "]";
        } else {
            forn(i, A.size()) {
                out << A[i] << endl;
            }
        }
        return out;
    }
};