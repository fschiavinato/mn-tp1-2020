#pragma once
#include"../macros.h"

/**
 * Implementación de matriz donde solo nos guardamos la mitad inferior
 * para utilizar en el algoritmo de Cholesky
 */
template <class T>
class matriz_mitad_inferior {
    private:
        T** entradas;
        int n;
    public:
        matriz_mitad_inferior(int n): n(n) {
            entradas = new T*[n];
            forn(i, n) {
                entradas[i] = new T[i+1];
                
                forn(j, i+1) entradas[i][j] = 0;
            }
        }

        ~matriz_mitad_inferior() {
            forn(i, n) {
                delete[] entradas[i];
            }
            delete[] entradas;
        }

        T* const operator[](int i) {
            return entradas[i];
        }

        friend ostream& operator<<(ostream& out, matriz_mitad_inferior<T>& v) {
            out << "[";
            forn(i, v.n) {
                out << endl << "[";
                forn(j, i+1) {
                    out << v[i][j] << " ";
                }
                out << "]," << endl;
            }
            out << "]";
            return out;
        }
};