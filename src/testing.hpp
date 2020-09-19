#include <iostream>
#include "rankings/cmm.hpp"
#include "rankings/wp.hpp"
#include "rankings/elo.hpp"
#include "macros.h"
#include "tipos/matriz.h"
#include "tipos/vector.h"
#include "tipos/partido.h"
#include <fstream>


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int method = stoi(argv[3]);
    int T, P;
    fin >> T;
    vect<etype> w(T), l(T);
    matriz<etype> n(T, T);
    vect<partido> partidos(P);
    forn(i, P) fin >> partidos[i];

    vect<etype> r;
    switch(method) {
        case 0:
            r = cmm<etype>(partidos, T);
            break;
        case 1:
            r = wp<etype>(partidos, T);
            break;
        case 2:
            r = elo<etype>(partidos, T);
            break;
    }
    fout << r << endl;
    return 0;
}