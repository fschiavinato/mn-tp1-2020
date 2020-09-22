#pragma once
#include"../tipos/vector.h"
#include"../tipos/partido.h"
#include"../tipos/matriz.h"
#include"../solvers/eg.hpp"
#include <math.h>
#define PI 3.14159265358979323846
#define CONSTANT_Q_ELO 0.0057565

etype gFunction(etype rd){
    return 1/sqrt(1+3*pow(CONSTANT_Q_ELO,2)*pow(rd,2)/pow(PI,2));
}

etype EFunction(etype rdj, etype diffElo, etype g){
    return 1/(1+pow(10, -g*diffElo/400));
}

etype dFunction(etype g, etype E){
    return pow(pow(CONSTANT_Q_ELO,2)*pow(g,2)*E*(1-E), -1);
}

etype calcNewRD(etype rd, etype d){
    return sqrt(pow(1/pow(rd,2)+1/d, -1));
}

pair<etype,etype> newRatingAndRD(etype r1, etype r2, etype rs1, etype rs2, int g1, int g2){
    etype outcome = g1 > g2 ? 1 : (g1 == g2 ? 1/2 : 0);

    etype g = gFunction(rs2);
    etype E = EFunction(rs2, r1-r2, g);
    etype d = dFunction(g, E);

    etype outcomeMinusExpected = outcome-E;
    etype newRating = r1 + CONSTANT_Q_ELO/(1/pow(rs1,2) + 1/d)*g*outcomeMinusExpected;
    etype newRD = calcNewRD(rs1, d);
    return make_pair(newRating, newRD);
}

template<class F>
vect<F> elo(vect<partido>& partidos, int T) {
    vect<etype>ratings(T, 1500);
    vect<etype>RDS(T, 350);

    for(int i = 0; i < partidos.size(); i++){
        auto r1 = ratings[partidos[i].equipo1];
        auto r2 = ratings[partidos[i].equipo2];
        auto rs1 = RDS[partidos[i].equipo1];
        auto rs2 = RDS[partidos[i].equipo2];
        auto z1 = newRatingAndRD(r1,r2,rs1,rs2,partidos[i].goles1,partidos[i].goles2);
        auto z2 = newRatingAndRD(r2,r1,rs2,rs1,partidos[i].goles2,partidos[i].goles1);
        ratings[partidos[i].equipo1] = z1.first;
        ratings[partidos[i].equipo2] = z2.first;
        RDS[partidos[i].equipo1] = z1.second;
        RDS[partidos[i].equipo2] = z2.second;
    }

    return ratings;
}