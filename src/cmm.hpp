#pragma once
#include"tipos/vector.h"
#include"tipos/racional.h"
#include"tipos/matriz.h"
#include"eg.hpp"

template<class F>
vect<F> cmm(vect<F>& w, vect<F>& l, matriz<F>& n, const int T) {
    matriz<F> C(T,T);
    vect<F> b(T);
    forn(i, T) {
        b[i] = (w[i] - l[i]) / 2 + 1;
        forn(j, T) {
            if(i == j) {
                C[i][j] = w[i] + l[i] + 2;
            }
            else {
                C[i][j] = -n[i][j];
            }
        }
    }
    return eg(C, b, T);
}