#include <iostream>
#include "rankings/cmm.hpp"
#include "rankings/wp.hpp"
#include "rankings/elo.hpp"
#include "macros.h"
#include "tipos/matriz.h"
#include "tipos/vector.h"
#include "tipos/partido.h"
#include <fstream>

typedef vect<etype>(*ranking)(vect<partido>&, int);

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int method = stoi(argv[3]);
    int T;
    fin >> T;
    vect<etype> w(T), l(T);
    matriz<etype> n(T, T);
    forn(i, T) forn(j, T) { 
        fin >> n[i][j];
        w[i] += n[i][j];
        l[j] += n[i][j];
    }
    forn(i, T) forsn(j, i, T) { 
        n[i][j] += n[j][i];
        n[j][i] = n[i][j]; 
    }
    vect<etype> r = cmm<etype>(w, l, n, T, false);
    fout << r;
    return 0;
}