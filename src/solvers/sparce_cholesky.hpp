#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz.h"
#include <math.h>

/**
  * Resolución de sistema Ax=b mediante la descomposición de Cholesky 
  * con matrices dispersa (sparse matrix).
  * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.146.1200&rep=rep1&type=pdf
  * https://github.com/scijs/cholesky-solve
  */
template<class F>
vect<F> cholesky(vect<F>& C, vect <F>& b, const int T) {
    vect<F> x(T);
    vect<F> y(T);
    cout << C << endl;
    cout << b << endl;
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
    //Lo igualamos del otro lado para poder hacer ambas sustituciones sin cambios
    forn(i,T)
        forn(j,T)
           if(j > i) C[i][j] = C[j][i];

    //resuelvo L * y = b con forward sustitution
    forn(i, T) {
        y[i] = b[i];
        forn(j, i) {
            y[i] -= C[i][j] * y[j];
        }
        y[i] = y[i] / C[i][i];
    }
    cout << y << endl;

    //resuelvo L^t * x = y con backward sustitution
    dforn(i, T) {
        x[i] = y[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }

    return x;
}