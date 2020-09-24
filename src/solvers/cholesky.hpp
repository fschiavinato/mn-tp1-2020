#pragma once
#include"../tipos/vector.h"
#include"../tipos/partido.h"
#include"../tipos/matriz_mitad_inferior.hpp"
#include <math.h>

/**
  * Resolución de sistema Ax=b mediante la descomposición de Cholesky 
  * la cual es A = L*L^t y luego resolvemos L*y=b y luego L^t*x=y.
  * SOLO APLICABLE SI LA MATRIZ DE ENTRADA ES SIMETRICA DEF POSITIVA.
  */
template<class F>
vect<F> cholesky(matriz_mitad_inferior<F>& C, vect <F>& b, const int T) {
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

template<class F>
vect<F> cmmWithCholesky(vect<partido>& partidos, int T){
    vect<F> partidosJugados(T), b(T,1);
    matriz_mitad_inferior<F> C(T);
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
        int eq1, eq2;
        if(partidos[i].equipo1 < partidos[i].equipo2){
            eq1 = partidos[i].equipo1;
            eq2 = partidos[i].equipo2;
        } else {
            eq2 = partidos[i].equipo1;
            eq1 = partidos[i].equipo2;
        }
        C[eq2][eq1] -= 1;
    }
    
    for(int i = 0; i < T; i++) 
        C[i][i] = 2+partidosJugados[i];


    return cholesky(C, b, T);
}