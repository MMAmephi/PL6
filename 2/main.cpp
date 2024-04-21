#include "Matrix.h"

int main(int argc, char* argv[]){
    std::cout << "Test with the wrong file name:" << std::endl;
    Matrix m("1.txt");
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

    std::cout << "Multiplying of matrix with dimensions (2,3) and (3, 2):" << std::endl;
    (m1*m2).print_m();
    std::cout << "Multiplying of matrix with dimensions (2,3) and (2,3):" << std::endl;
    (m1*m3).print_m();

    Matrix m_null(2, 3);
    std::cout << "Multiplying by zero matrix:" << std::endl;
    (m2*m_null).print_m();
   
    std::cout << "Addition of matrix with dimensions (2,3) and (3, 2):" << std::endl;
    (m1+m2).print_m();
    std::cout << "Addition of matrix with dimensions (2,3) and (2,3):" << std::endl;
    (m1+m3).print_m();
    std::cout << "Addition of zero matrix:" << std::endl;
    (m1+m_null).print_m();

    std::cout << "Addition of double number:" << std::endl;
    (m1+2.).print_m();
    std::cout << "Multiplying by double number:" << std::endl;
    (m1*2.).print_m();
    std::cout << "Addition of zero(double number):" << std::endl;
    (m2+0.).print_m();
    std::cout << "Multiplying by zero:" << std::endl;
    (m2*0.).print_m();

    std::cout << "Element (1,1) of matrix from the file:" << std::endl;
    std::cout << m1.get(1, 1) << std::endl;
    std::cout << "Element (3,3) from  matrix with demensions (2,3):" << std::endl;
    std::cout << m1.get(3, 3) << std::endl;
    std::cout << "Changing element (3,3) in matrix with dimensions (2,3):" << std::endl;
    m1.change(3, 3, 2.);


    Matrix result = (m1+m3)*m2;
    std::cout << "Matrix written in the file result.txt:" << std::endl;
    result.print_m();
    result.write_m("result.txt");
    
    return 0;
}
