#include<iostream>
#include<vector>
#include<ostream>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define debug(x) cerr << #x << ":" << endl << x << endl

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

        friend ostream& operator<<(ostream& out, matriz<T>& A) {
            out << "{";
            forn(i, A.n) {
                out << "{";
                forn(j, A.m) {
                    out << A[i][j] << (j < A.m-1? "; ": "");
                }
                out << "}" << (i < A.n-1? "; ": "") << endl;
            }
            out << "}";
            return out;
        }
};

vector<float> cmm(vector<int>& w, vector<int>& l, matriz<int>& n, const int T);
vector<float> eg(matriz<float>& C, vector<float>& b, const int T);

int main() {
    int T, P;
    cin >> T >> P;
    vector<int> w(T), l(T);
    matriz<int> n(T,T);
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
    vector<float> r = cmm(w, l, n, T);
    forn(i, T) {
        cout << r[i] << endl;
    }
}

vector<float> cmm(vector<int>& w, vector<int>& l, matriz<int>& n, const int T) {
    matriz<float> C(T,T);
    vector<float> b(T);
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

vector<float> eg(matriz<float>& C, vector <float>& b, const int T) {
    debug(C);
    vector<float> x(T);
    forn(i, T) {
        forsn(k, i+1, T) {
            forsn(j, i, T) {
                C[k][j] -= C[i][j] * C[k][i] / C[i][i];
                b[k] -= b[i] * C[k][i] / C[i][i];
            }
        }
    }
    debug(C);
    dforn(i, T) {
        x[i] = b[i];
        dforsn(j, i+1, T) {
            x[i] -= C[i][j] * x[j];
        }
        x[i] = x[i] / C[i][i];
    }
    return x;
}
