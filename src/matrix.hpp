#include <vector>
#include <iostream>

#define eps 10e-6

using namespace std;
typedef vector<double> Row;

//Para comparar numeros
bool isEqual(double x, double y){
    return abs(x-y) < eps;
}

class matrix {
    public:
        //Constructor, crea una matriz de rows x cols con todos sus valores en 0
        matrix(int rows, int cols);

        //Para inicializar pasandole una matriz
        matrix(const vector<vector<double>>&);

        //Devuelve un elemento de la matriz
        double operator()(int row, int col) const;

        //Define un valor en la matriz
        void defValue(int row, int col, double value);

        //Devuelve la cantidad de filas
        int rowAmount();

        //Devuelve la cantidad de columnas
        int colAmount();

        //Para acceder a las filas de la matriz
        vector<Row> rows();


    private:
        int rowSize;
        int colSize;
        vector<Row> mRows;
};

matrix::matrix(int rows, int cols):
    rowSize(rows), colSize(cols), mRows(rows, vector<double> (cols, 0.0)) {}

matrix::matrix(const vector<vector<double>>& m):
    rowSize(m.size()), colSize(m[0].size()), mRows(m.size(), vector<double> (m[0].size(), 0.0))
{
    for(int i = 0; i < this->rowSize; i++) {
        for(int j = 0; j < this->colSize; j++) {
            defValue(i,j,m[i][j]);
        }
    }
}

double matrix::operator()(int row, int col) const {
    //Chequea que el elemento que se quiere devolver este dentro de los limites de la matriz
    if(row >= this->rowSize || col >= this->colSize) {
        return 0;
    }
    else {
        return this->mRows[row][col];
    }
}

void matrix::defValue(int row, int col, double value) {
    this->mRows[row][col] = value;
}

int matrix::rowAmount() {
    return this->rowSize;
}

int matrix::colAmount() {
    return this->colSize;
}

vector<Row> matrix::rows() {
    return this->mRows;
}

//Imprime la matriz
void printMatrix(matrix& m) {
    for(int i = 0; i < m.rowAmount(); i++) {
		for(int j = 0; j < m.colAmount(); j++) {
			cout << m(i,j) << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

void printVector(vector<double>& v) {
    cout << "[";
    for(int i = 0; i < v.size(); i++) {
        if(i == v.size()-1) {
            cout << v[i];
        }
        else {
            cout << v[i] << ",";
        }
    }
    cout << "]" << '\n';
}

//Eliminacion Gaussiana
vector<double> gaussianElimination(matrix& m, vector<double> v) {
    for(int i = 0; i < m.rowAmount()-1; i++) {
        //Esto triangula la matriz
        for(int j = i+1; j < m.rowAmount(); j++) {
        	double coef = m(j,i) / m(i,i);
            if(!isEqual(coef,0)) {
                for (int k = 0; k < m.rows()[i].size(); k++) {
                    double value = m.rows()[i][k];
                    m.defValue(j, k, m(j, k) - coef * value);
                }
            }

        //Esto modifica el vector independiente
        	v[j] = v[j] - (v[i] * coef);
    	}
    }

    //Al salir de este for la matriz esta triangulada y el vector independiente modificado de acuerdo a las operaciones que se llevaron a cabo

    //Inicializa el vector de incognitas, que luego sera modificado con las soluciones a cada una de ellas
    vector<double> incognitas(m.rowAmount(), 0.0);

    for (int row = incognitas.size()-1; row >= 0; row--) {
        double sum = 0;
        for (int k = 0; k < m.rows()[row].size(); k++) {
            if (k > row) {
                double value = m.rows()[row][k];
                sum += value * incognitas[k];
            }
        }
        incognitas[row] = (v[row] - sum) / m(row, row);
    }
    return incognitas;
}
