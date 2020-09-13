#include<iostream>
#include"cmm.hpp"
#include"macros.h"
#include"tipos/matriz.h"
#include"tipos/vector.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    string method = argv[3];
    int T, P;
    fin >> T >> P;
    vect<double> w(T), l(T);
    matriz<double> n(T, T);
    int fecha, equipo1, equipo2, goles1, goles2;
    forn(i, P) {
        fin >> fecha >> equipo1 >> goles1 >> equipo2 >> goles2;
        if(goles1 > goles2) {
            w[equipo1-1]++;
            l[equipo2-1]++;
        }
        else {
            w[equipo2-1]++;
            l[equipo1-1]++;
        }
        n[equipo1-1][equipo2-1]++;
        n[equipo2-1][equipo1-1]++;
    }
    vect<double> r = cmm(w, l, n, T);
    forn(i, T) {
        fout << r[i] << endl;
    }
}
