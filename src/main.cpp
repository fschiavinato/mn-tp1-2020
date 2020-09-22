#include <iostream>
#include "rankings/cmm.hpp"
#include "rankings/wp.hpp"
#include "rankings/elo.hpp"
#include "macros.h"
#include "tipos/matriz.h"
#include "tipos/vector.h"
#include "tipos/partido.h"
#include <fstream>
#include <map>
#include <chrono>
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

    auto start = std::chrono::steady_clock::now();
    
    vector<ranking> rankings = {cmmWithEg<etype>, wp<etype>, elo<etype>, cmmWithCholesky<etype>};

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    ofstream timeFile(string(argv[2])+".log");
    timeFile << elapsed_seconds.count();

    r = rankings[method](partidos, T);
    fout << r;
    return 0;
}
#else
#include"no_matches.hpp"
#endif

