#include <iostream>
#include "rankings/cmm.hpp"
#include "rankings/wp.hpp"
#include "rankings/elo.hpp"
#include "macros.h"
#include "tipos/matriz.h"
#include "tipos/vector.h"
#include "tipos/partido.h"
#include <fstream>
using namespace std;

typedef vect<etype>(*ranking)(vect<partido>&, int);

#ifndef NO_MATCHES
int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int method = stoi(argv[3]);
    int T, P;
    fin >> T >> P;
    vect<etype> w(T), l(T);
    matriz<etype> n(T, T);
    vect<partido> partidos(P);
    forn(i, P) fin >> partidos[i];
    vect<etype> r;
    vector<ranking> rankings = {cmmWithEg<etype>, wp<etype>, elo<etype>, cmmWithCholesky<etype>};
    r = rankings[method](partidos, T);
    fout << r;
    return 0;
}
#else
#include"no_matches.hpp"
#endif

