#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz_dispersa.hpp"
#include"../tipos/partido.h"
#include <math.h>

/**
  * Resolución de sistema Ax=b mediante la descomposición de Cholesky 
  * con matrices dispersas.
  * Utilizamos un vector de vectores de tuplas donde el primer valor es la fila,
  * y las tuplas contienen el primer valor la columna y el segundo el valor en la matriz.
  * Las tuplas las mantenemos ordenadas por la columna.
  * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.146.1200&rep=rep1&type=pdf
  * https://github.com/scijs/cholesky-solve
  */

template<class F>
vect<F> choleskySparse(matriz_dispersa<F>& C, vect <F>& b, const int T) {
    vect<F> x(T);
    vect<F> y(T);
    
    forn(j, T) {
        
        F sum = C.sumarFilaCuadrado(j, 0, j-1);
        C.asignar(j,j,sqrt(C.obtener(j,j)-sum));

        forsn(i, j+1, T) {
            F sum2 = C.productoInternoFilas(i, j, 0, j-1);
            C.asignar(i,j, (C.obtener(i,j)-sum2)/C.obtener(j,j));
        }
    }
    
    //resuelvo L * y = b con forward sustitution
    forn(i, T) {
        y[i] = b[i];
        y[i] -= C.productoInternoFilaContraVector(i, 0, i-1, y);
        y[i] = y[i] / C.obtener(i,i);
    }

    //resuelvo L^t * x = y con backward sustitution
    dforn(i, T) {
        x[i] = y[i];
        dforsn(j, i+1, T) {
            x[i] -= C.obtener(i,j) * x[j];
        }
        x[i] = x[i] / C.obtener(i,i);
    }

    return x;
}

template<class F>
vect<F> cmmConCholeskyDisperso(vect<partido>& partidos, int T){

    vect<F> partidosJugados(T), b(T,1);
    matriz_dispersa<F> C(T);

    for(int i = 0; i < partidos.size(); i++) {
        if(partidos[i].goles1 > partidos[i].goles2) {
            b[partidos[i].equipo1] += 0.5;
            b[partidos[i].equipo2] -= 0.5;
        }
        else {
            b[partidos[i].equipo1] -= 0.5;
            b[partidos[i].equipo2] += 0.5;
        }
        partidosJugados[partidos[i].equipo1]++;
        partidosJugados[partidos[i].equipo2]++;
        C.sumarValor(partidos[i].equipo1,partidos[i].equipo2, -1);
    }
    
    for(int i = 0; i < T; i++) 
        C.asignar(i, i, 2+partidosJugados[i]);

    return choleskySparse<F>(C, b, T);
}