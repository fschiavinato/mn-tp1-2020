#include"tipos/vector.h"
#include"tipos/racional.h"
#include"tipos/matriz.h"
#include"tipos/partido.h"

template<class F>
vect<F> wp(vect<partido>& partidos, int T){
    vect<F> w(T), p(T), r(T);
    for(int i = 0; i < partidos.size(); i++) {
    	p[partidos[i].equipo1-1]++;
    	p[partidos[i].equipo2-1]++;

        if(partidos[i].goles1 > partidos[i].goles2) {
            w[partidos[i].equipo1-1]++;
        }
        else {
            w[partidos[i].equipo2-1]++;
        }
    }
    for(int i = 0; i < T; i++) {
    	r[i] = w[i] / p[i];
    }
    return r;
}
