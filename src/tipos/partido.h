#pragma once
struct partido {
    int fecha;
    int goles1;
    int goles2;
    int equipo1;
    int equipo2;
    friend istream& operator>>(istream& in, partido& p) {
        return in >> p.fecha >> p.equipo1 >> p.goles1 >> p.equipo2 >> p.goles2;
    };
    friend ostream& operator<<(ostream& out, partido& v) {
        out << v.fecha << " " << v.equipo1 << " " << v.goles1 << " " << v.equipo2 << " " << v.goles2;
        return out;
    }
};