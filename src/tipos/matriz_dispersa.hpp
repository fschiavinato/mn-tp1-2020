#pragma once
#include"../macros.h"
#include <stdexcept>
#include <algorithm>

bool cmpPairs(const pair<int,etype> &a, const pair<int,etype> &b){
    return a.first < b.first;
}
/**
 * Vector de filas que contiene un vector de tuplas
 * donde el primer elemento es la columna y el segundo el valor en la matriz
 * Las tuplas las mantenemos ordenadas por la columna.
 */
template <class T>
class matriz_dispersa {
    private: 
        vector<vector<pair<int,etype>>> valores;
        int n;
    public:
        matriz_dispersa(int n) : n(n), valores(vector<vector<pair<int,etype>>>(n)){};

        vector<pair<int,etype>>& operator[](int index) 
        { 
            return valores[index]; 
        } 

        int size(){ return n; }

        T obtener(int i, int j) {
            auto it = lower_bound(valores[i].begin(), valores[i].end(), make_pair(j-1, 0), cmpPairs);
            if(it != valores[i].end() and it->first == j-1)
                it++;
            if(it != valores[i].end() and it->first == j)
                return it->second;
            return 0;
        }
        void asignar(int fila, int col, T v){
            if(v == 0)
                return;

            if(col > fila)
                swap(col, fila); //simétrica
            
            auto itLugar = lower_bound(valores[fila].begin(), valores[fila].end(), make_pair(col-1,0), cmpPairs);
            if(itLugar != valores[fila].end() and itLugar->first == col-1)
                itLugar++;
            
            if(itLugar != valores[fila].end() and itLugar->first == col)
                itLugar->second = v;
            else
                valores[fila].insert(itLugar, make_pair(col, v));
        }
        void sumarValor(int fila, int col, T v){
            if(v == 0)
                return;

            if(col > fila)
                swap(col, fila); //simétrica
            
            auto itLugar = lower_bound(valores[fila].begin(), valores[fila].end(), make_pair(col-1,0), cmpPairs);
            
            if(itLugar != valores[fila].end() && itLugar->first == col-1)
                itLugar++;
            
            if(itLugar != valores[fila].end() and itLugar->first == col)
                itLugar->second += v;
            else
                valores[fila].insert(itLugar, make_pair(col, v));
        }
        T sumarFilaCuadrado(int fila, int columnaPrincipio, int columnaFinal) {
            //Buscamos la columna con búsqueda binaria
            auto it = lower_bound(valores[fila].begin(), valores[fila].end(), make_pair(columnaPrincipio-1, 0), cmpPairs);

            if(it == valores[fila].end())
                return 0;

            if(it->first == columnaPrincipio-1)
                it++;

            auto itFinal = lower_bound(valores[fila].begin(), valores[fila].end(), make_pair(columnaFinal, 0), cmpPairs);

            if(itFinal != valores[fila].end() && itFinal->first == columnaFinal)
                itFinal++;

            T suma = 0;
            while(it != itFinal && it != valores[fila].end()){
                suma += it->second*it->second;
                it++;
            }
            return suma;
        }

        T productoInternoFilas(int fila1, int fila2, int columnaPrincipio, int columnaFinal) {
            T suma = 0;
            //Buscamos las filas
            auto itPrimero = lower_bound(valores[fila1].begin(), valores[fila1].end(), make_pair(columnaPrincipio-1,0), cmpPairs);
            
            if(itPrimero != valores[fila1].end() && itPrimero->first == columnaPrincipio-1)
                itPrimero++;

            auto itSegundo = lower_bound(valores[fila2].begin(), valores[fila2].end(), make_pair(columnaPrincipio-1,0), cmpPairs);
            
            if(itSegundo != valores[fila2].end() && itSegundo->first == columnaPrincipio-1)
                itSegundo++;

            //Vamos avanzando ambos iteradores
            while(itPrimero != valores[fila1].end() && itSegundo != valores[fila2].end() && itPrimero->first <= columnaFinal){
                if(itPrimero->first < itSegundo->first)
                    itPrimero++;
                else 
                    if(itSegundo->first < itPrimero->first)
                        itSegundo++;
                    else {
                        suma += itPrimero->second*itSegundo->second;
                        itPrimero++;
                        itSegundo++;
                    }
            }
            return suma;
        }

        T productoInternoFilaContraVector(int fila, int columnaPrincipio, int columnaFinal, vect<T>& vec){
            T suma = 0;
            //Buscamos la columna
            auto itPrimero = lower_bound(valores[fila].begin(), valores[fila].end(), make_pair(columnaPrincipio-1,0), cmpPairs);
            
            if(itPrimero != valores[fila].end() && itPrimero->first == columnaPrincipio-1)
                itPrimero++;

            while(itPrimero != valores[fila].end() && itPrimero->first <= columnaFinal){
                suma += itPrimero->second*vec[itPrimero->first];
                itPrimero++;
            }
            
            return suma;
        }

        friend ostream& operator<<(ostream& out, matriz_dispersa<T>& v) {
            out << "[";
            forn(i, v.size()) {
                out << "[";
                forn(j, v[i].size()) {
                    out << "{" << v[i][j].first << "," << v[i][j].second << "}, ";
                }
                out << "]" << endl;
            }
            out << "]";
            return out;
        }
};