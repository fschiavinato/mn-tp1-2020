#pragma once
#include"../macros.h"

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
                
                forn(j, n) entradas[i][j] = 0;
            }
        }

        ~matriz() {
            forn(i, n) {
                delete[] this->entradas[i];
            }
            delete[] this->entradas;
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