#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz.h"
#include"../tipos/partido.h"
#include"../solvers/eg.hpp"
#include"../solvers/cholesky.hpp"

template<class F>
vect<F> cmm(vect<partido>& partidos, int T){
    vect<F> w(T), l(T);
    matriz<F> n(T, T);
    for(int i = 0; i < partidos.size(); i++) {
        if(partidos[i].goles1 > partidos[i].goles2) {
            w[partidos[i].equipo1]++;
            l[partidos[i].equipo2]++;
        }
        else {
            w[partidos[i].equipo2]++;
            l[partidos[i].equipo1]++;
        }
        n[partidos[i].equipo1][partidos[i].equipo2]++;
        n[partidos[i].equipo2][partidos[i].equipo1]++;
    }
    return cmm(w, l, n, T);
}

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

template<class F>
vect<F> cmmWithEg(vect<partido>& partidos, int T){
    return cmm<F>(partidos, T);
}