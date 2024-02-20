#include "Matrix.h"

int main(int argc, char* argv[]){
    Matrix m1("matrix.txt");

    Matrix m2(3,2);
    m2.change(0, 0, 1.0);
    m2.change(0, 1, 2.0);
    m2.change(1, 0, 3.0);
    m2.change(1, 1, 4.0);
    m2.change(2, 0, 5.0);
    m2.change(2, 1, 6.0);

    double ar1[6] {1., 2., 3., 4., 5., 6.};
    Matrix m3(2, 3, ar1);

    Matrix result = (m1 + m3)*m2;
    result.print_m();
    result.write_m("result.txt");
    
    return 0;
}