#include <iostream>
#include <fstream>

class Matrix {
private:
    int n_row;
    int m_col;
    double** data;
    
public:
    Matrix();
    Matrix(int row, int col);
    Matrix(int row, int col, double* arr);
    Matrix(std::string file_in);
    ~Matrix();

    double get(int i, int j);
    void print_m();
    void write_m(std::string file_out);

    void change(int i, int j, double value);

    Matrix operator+(Matrix other);
    Matrix operator*(Matrix other);
    Matrix operator+(double value);
    Matrix operator*(double value);
};