#pragma once
#include"tipos/vector.h"
#include"tipos/racional.h"
#include"tipos/matriz.h"

template<class F>
vect<F> eg(matriz<F>& C, vect <F>& b, const int T) {
    vect<F> x(T);
    debug(C);
    debug(b);
    forn(i, T) {
        debug(i);
        forsn(k, i+1, T) {
            F alpha = C[k][i] / C[i][i];
            debug(k);
            debug(alpha);
            forsn(j, i, T) {
                C[k][j] -= C[i][j] * alpha;
            }
            b[k] -= b[i] * alpha;
            debug(C);
            debug(b);
            RAYA;
        }
        RAYA;
    }
    RAYA;
    debug(C);
    debug(b);
    dforn(i, T) {
        x[i] = b[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }
    return x;
}