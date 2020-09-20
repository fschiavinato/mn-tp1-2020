#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz.h"

template<class F>
vect<F> eg(matriz<F>& C, vect <F>& b, const int T) {
    vect<F> x(T);

    forn(j, T) {
        
        F sum = 0;
        forn(k, j-1) sum += C[j][k]*C[j][k];

        C[j][j] = sqrt(C[j][j]-sum);

        forsn(i, j+1, T) {
            F sum2 = 0;
            forn(k, j-1) sum2 += C[i][k]*C[j][k];

            C[i][j] = 1/C[j][j] * (C[i][j]-sum2);
        }
    }

    //resuelvo L * y = b
    dforn(i, T) {
        x[i] = b[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }

    //resuelvo L^t * x = b MAL
    dforn(i, T) {
        x[i] = b[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }

    return x;
}