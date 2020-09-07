#include<iostream>
#include<vector>
#include<ostream>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define debug(x) cerr << __LINE__  << ") " << #x << " = " << x << endl
#define RAYA cerr << "===============================" << endl

using namespace std;

template <class T>
class matriz {
    private:
        T** entradas;
        int n, m;
    public:
        matriz(int n, int m): n(n), m(m) {
            this->entradas = new T*[n];
            forn(i, n) {
                this->entradas[i] = new T[m];
            }
        }

        ~matriz() {
            forn(i, n) {
                delete this->entradas[i];
            }
            delete this->entradas;
        }

        T* const operator[](int i) {
            return this->entradas[i];
        }

        friend ostream& operator<<(ostream& out, matriz<T>& v) {
            out << "[";
            forn(i, v.n) {
                out << endl << "[";
                forn(j, v.m) {
                    out << v[i][j] << (j < v.m-1? ", ": "");
                }
                out << "]" << (i < v.n-1? ", ": "");
            }
            out << "]";
            return out;
        }
};

template<class T>
class vect: public std::vector<T> {
    public:
    vect(const int& n): std::vector<T>(n) {}
    friend ostream& operator<<(ostream& out, vect<T>& A) {
        out << "[";
        forn(i, A.size()) {
            out << A[i] << (i < A.size()-1? ", ": "");
        }
        out << "]";
        return out;
    }
};

vect<double> cmm(vect<double>& w, vect<double>& l, matriz<double>& n, const int T);
vect<double> eg(matriz<double>& C, vect<double>& b, const int T);

int main() {
    int T, P;
    cin >> T >> P;
    vect<double> w(T), l(T);
    matriz<double> n(T, T);
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
    vect<double> r = cmm(w, l, n, T);
    forn(i, T) {
        cout << r[i] << endl;
    }
}

vect<double> cmm(vect<double>& w, vect<double>& l, matriz<double>& n, const int T) {
    matriz<double> C(T,T);
    vect<double> b(T);
    forn(i, T) {
        b[i] = 1 + (w[i] - l[i]) / 2;
        forn(j, T) {
            if(i == j) {
                C[i][j] = 2 + w[i] + l[i];
            }
            else {
                C[i][j] = -n[i][j];
            }
        }
    }
    return eg(C, b, T);
}

vect<double> eg(matriz<double>& C, vect <double>& b, const int T) {
    vect<double> x(T);
    debug(C);
    debug(b);
    forn(i, T) {
        debug(i);
        forsn(k, i+1, T) {
            double alpha = C[k][i] / C[i][i];
            debug(k);
            debug(alpha);
            forsn(j, i, T) {
                C[k][j] -= C[i][j] * alpha;
            }
            b[k] -= b[i] * alpha;
            debug(C);
            debug(b);
            RAYA;
        }
        RAYA;
    }
    RAYA;
    debug(C);
    debug(b);
    dforn(i, T) {
        x[i] = b[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }
    return x;
}
