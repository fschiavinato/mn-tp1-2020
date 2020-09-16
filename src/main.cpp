#include <iostream>
#include "cmm.hpp"
#include "elo.hpp"
#include "macros.h"
#include "tipos/matriz.h"
#include "tipos/vector.h"
#include "tipos/partido.h"
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
    vector<partido> partidos(P);
    int fecha, equipo1, equipo2, goles1, goles2;
    forn(i, P) {
        fin >> fecha >> equipo1 >> goles1 >> equipo2 >> goles2;
        partidos[i].fecha = fecha;
        partidos[i].equipo1 = equipo1;
        partidos[i].equipo2 = equipo2;
        partidos[i].goles1 = goles1;
        partidos[i].equipo2 = equipo2;

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

    vect<double> r;
    if(method == "cmm")
        r = cmmWrapper<double>(partidos, T);

    else if(method == "elo")
        r = elo<double>(partidos, T);

    
    fout << r << endl;
}
