#pragma once
#include"../tipos/vector.h"
#include"../tipos/matriz.h"
#include"../tipos/partido.h"

template<class F>
vect<F> wp(vect<partido>& partidos, int T){
    vect<F> w(T), p(T), r(T);
    for(int i = 0; i < partidos.size(); i++) {
    	p[partidos[i].equipo1]++;
    	p[partidos[i].equipo2]++;

        if(partidos[i].goles1 > partidos[i].goles2) {
            w[partidos[i].equipo1]++;
        }
        else {
            w[partidos[i].equipo2]++;
        }
    }
    for(int i = 0; i < T; i++) {
        if(p[i] != 0)
    	    r[i] = w[i] / p[i];
    }
    return r;
}
