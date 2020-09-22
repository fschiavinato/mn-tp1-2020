#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz.h"
#include <math.h>

/**
  * Resolución de sistema Ax=b mediante la descomposición de Cholesky 
  * la cual es A = L*L^t y luego resolvemos L*y=b y luego L^t*x=y.
  * SOLO APLICABLE SI LA MATRIZ DE ENTRADA ES SIMETRICA DEF POSITIVA.
  */
template<class F>
vect<F> cholesky(matriz<F>& C, vect <F>& b, const int T) {
    vect<F> x(T);
    vect<F> y(T);
    forn(j, T) {
        
        F sum = 0;
        forn(k, j) 
            sum += C[j][k]*C[j][k];

        C[j][j] = sqrt(C[j][j]-sum);

        forsn(i, j+1, T) {
            F sum2 = 0;
            forn(k, j) 
                sum2 += C[i][k]*C[j][k];

            C[i][j] = (C[i][j]-sum2)/C[j][j];
        }
    }

    //resuelvo L * y = b con forward sustitution
    forn(i, T) {
        y[i] = b[i];
        forn(j, i) {
            y[i] -= C[i][j] * y[j];
        }
        y[i] = y[i] / C[i][i];
    }

    //resuelvo L^t * x = y con backward sustitution
    dforn(i, T) {
        x[i] = y[i];
        dforsn(j, i+1, T) {
            x[i] -= C[j][i] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }

    return x;
}