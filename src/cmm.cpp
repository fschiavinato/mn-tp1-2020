#include<iostream>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)

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

};

float* const cmm(int w[], int l[], matriz<int>& n, const int T);
void eg(matriz<float>& C, float b[], const int T);

int main() {
    int T, P;
    int w[T], l[T];
    matriz<int> n(T,T);
    int fecha, equipo1, equipo2, goles1, goles2;
    cin >> T >> P;
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
    }
    float* r = cmm(w, l, n, T);
    forn(i, T) {
        cout << r[i] << endl;
    }
    delete[] r;
}

float* const cmm(int w[], int l[], matriz<int>& n, const int T) {
    matriz<float> C(T,T);
    float* b = new float[T];
    forn(i, T) {
        b[i] = 1 + (w[i] - l[i]) / 2;
        forn(j, T) {
            if(i == j) {
                C[i][j] = 2 + n[i][j];
            }
            else {
                C[i][j] = -n[i][j];
            }
        }
    }
    eg(C, b, T);
    return b;
}

void eg(matriz<float>& C, float b[], const int T) {
    forn(i, T) {
        forsn(j, i, T) {
            forsn(k, j, T) {
                C[j][k] = C[j][k] - C[i][k] * C[j][i] / C[i][i];
                b[j] = b[j] - b[i] * C[j][i];
            }
        }
    }
}
