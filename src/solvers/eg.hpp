#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz.h"

/**
  * Resolución de sistema Ax=b mediante la eliminación de gauss
  */
template<class F>
vect<F> eg(matriz<F>& C, vect <F>& b, const int T) {
    vect<F> x(T);

    forn(i, T) {
        forsn(k, i+1, T) {
            F alpha = C[k][i] / C[i][i];

            forsn(j, i, T) {
                C[k][j] -= C[i][j] * alpha;
            }
            b[k] -= b[i] * alpha;
        }
    }
    //resuelvo con backward sustitution
    dforn(i, T) {
        x[i] = b[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }
    return x;
}