#include "matrix.hpp"
#include <iostream>
#include <string>
using namespace std;

/*matrix buildColleyMatrix() {

}*/




int main() {
    //matrix m2({{1,2,3}, {1,2,3}, {1,1,1}, {2,3,4}, {2,3,4}});
    //printMatrix(m2);
    //matrix m1(10,10);
    //m1.defValue(1,1,23);
    //cout << m1.row_amount() << " " <<  m1.col_amount() << endl;
    //cout << m1(1,1) << endl;
    //cout << m2(0,0);

    matrix m3({{1,-3,1}, {2,-8,8}, {-6,3,-15}});
    vector<double> v = {4,-2,9};
    vector<double> res = gaussianElimination(m3,v);
    printVector(res);
}
