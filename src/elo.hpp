#pragma once
#include"tipos/vector.h"
#include"tipos/racional.h"
#include"tipos/partido.h"
#include"tipos/matriz.h"
#include"eg.hpp"
#include <math.h>
#define CONSTANT_Q_ELO 0.0057565

double gFunction(double rd){
    return 1/sqrt(1+3*pow(CONSTANT_Q_ELO,2)*pow(rd,2)/pow(M_PI,2));
}

double EFunction(double rdj, double diffElo, double g){
    return 1/1+pow(10, -g*diffElo/400);
}

double dFunction(double rdj, double g, double E){
    return pow(pow(CONSTANT_Q_ELO,2)*pow(g,2)*E*(1-E), -1);
}

double calcNewRD(double rd, double d){
    return sqrt(pow(1/pow(rd,2)+1/d, -1));
}

pair<double,double> newRatingAndRD(double r1, double r2, double rs1, double rs2, int g1, int g2){
    double outcome = g1 > g2 ? 1 : g1 == g2 ? 1/2 : 0;

    double g = gFunction(r2);
    double E = EFunction(r2, r2-r1, g);
    double d = dFunction(r2, g, E);

    double newRating = r1 + CONSTANT_Q_ELO/(1/pow(r1,2) + 1/d)*g*(outcome-E);
    double newRD = calcNewRD(r1, d);
    return make_pair(newRating, newRD);
}

template<class F>
vect<F> elo(vector<partido>& partidos, int T) {
    vect<double>ratings(T, 1500);
    vect<double>RDS(T, 350);

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