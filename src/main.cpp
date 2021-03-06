#include <iostream>
#include "rankings/cmm.hpp"
#include "rankings/wp.hpp"
#include "rankings/elo.hpp"
#include "solvers/cholesky_disperso.hpp"
#include "solvers/cholesky.hpp"
#include "macros.h"
#include "tipos/matriz.h"
#include "tipos/vector.h"
#include "tipos/partido.h"
#include <fstream>
#include <map>
#include <chrono>
#include <iomanip>      // std::setprecision
using namespace std;

typedef vect<etype>(*ranking)(vect<partido>&, int);

#ifndef NO_MATCHES
int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int method = stoi(argv[3]);
    int T, P;
    fin >> T >> P;
    map<int,int> mapaIdentificadores;
    vect<etype> w(T), l(T);
    matriz<etype> n(T, T);
    vect<partido> partidos(P);
    int contadorEquipo = 0;
    forn(i, P){
        fin >> partidos[i];
        if(mapaIdentificadores.count(partidos[i].equipo1) > 0){
            partidos[i].equipo1 = mapaIdentificadores[partidos[i].equipo1];
        } else {
            mapaIdentificadores.insert(make_pair(partidos[i].equipo1, contadorEquipo));
            partidos[i].equipo1 = contadorEquipo;
            contadorEquipo++;
        }

        if(mapaIdentificadores.count(partidos[i].equipo2) > 0){
            partidos[i].equipo2 = mapaIdentificadores[partidos[i].equipo2];
        } else {
            mapaIdentificadores.insert(make_pair(partidos[i].equipo2, contadorEquipo));
            partidos[i].equipo2 = contadorEquipo;  
            contadorEquipo++;
        }
    } 
    vect<etype> r;
    
    vector<ranking> rankings = {cmmWithEg<etype>, wp<etype>, elo<etype>, cmmWithCholesky<etype>, cmmConCholeskyDisperso<etype>};
    r = rankings[method](partidos, T);

    fout << setprecision(14) << r;
    return 0;
}
#else
#include"no_matches.hpp"
#endif

