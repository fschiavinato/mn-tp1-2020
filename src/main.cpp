#include<iostream>
#include"cmm.hpp"
#include"macros.h"
#include"tipos/matriz.h"
#include"tipos/vector.h"
using namespace std;

int main() {
    int T, P;
    cin >> T >> P;
    vect<racional> w(T), l(T);
    matriz<racional> n(T, T);
    int fecha, equipo1, equipo2, goles1, goles2;
    forn(i, P) {
        cin >> fecha >> equipo1 >> goles1 >> equipo2 >> goles2;
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
    vect<racional> r = cmm(w, l, n, T);
    forn(i, T) {
        cout << r[i] << endl;
    }
}
