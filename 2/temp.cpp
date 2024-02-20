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

    Matrix operator+(Matrix& other);
    Matrix operator*(Matrix& other);
    Matrix operator+(double value);
    Matrix operator*(double value);
};


Matrix::Matrix() : n_row(0), m_col(0), data(nullptr) {};

Matrix::Matrix(int n, int m) {
    n_row = n;
    m_col = m;
    data = new double*[n_row];
    for (int i = 0; i < n_row; ++i) {
        data[i] = new double[m_col];
        for(int j=0; j < m_col; ++j){
            data[i][j] = .0;
        }
    }
};

Matrix::Matrix(int n, int m, double* arr) {
    n_row = n;
    m_col = m;
    data = new double*[n_row];
    for (int i = 0; i < n_row; ++i) {
        data[i] = new double[m_col];
        for(int j=0; j < m_col; ++j){
            data[i][j] = arr[i*m_col + j];
        }
    }
};

Matrix::~Matrix() {
    if (data != nullptr) {
        for (int i = 0; i < n_row; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
};

Matrix::Matrix(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> n_row >> m_col;
        data = new double*[n_row];
        for (int i = 0; i < n_row; ++i) {
            data[i] = new double[m_col];
            for (int j = 0; j < m_col; ++j) {
                file >> data[i][j];
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
};

double Matrix::get(int i, int j) {
    if (i >= 0 && i < n_row && j >= 0 && j < m_col) {
        return data[i][j];
    } else {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return 0.0;
    }
};

void Matrix::print_m() {
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
};

void Matrix::write_m(std::string file_out) {
    std::ofstream file(file_out);
    if (file.is_open()) {
        file << n_row << " " << m_col << std::endl;
        for (int i = 0; i < n_row; ++i) {
            for (int j = 0; j < m_col; ++j) {
                file << data[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
};

void Matrix::change(int i, int j, double value) {
    if (i >= 0 && i < n_row && j >= 0 && j < m_col) {
        data[i][j] = value;
    } else {
        std::cout << value;
        std::cerr << "Error: Index out of bounds." << std::endl;
    }
};

Matrix Matrix::operator+(Matrix& other) {
    if (n_row != other.n_row || m_col != other.m_col) {
        std::cerr << "Error: Matrix dimensions do not match for addition." << std::endl;
        return Matrix();
    }
    Matrix result(n_row, m_col);
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
};

Matrix Matrix::operator*(Matrix& other){
    if (m_col != other.n_row) {
            std::cerr << "Error: Matrix dimensions do not match for multiplication." << std::endl;
            return Matrix();
        }
    Matrix result(n_row, other.m_col);
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < other.m_col; ++j) {
            for (int k = 0; k < m_col; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
};

Matrix Matrix::operator+(double value){
    Matrix result(n_row, m_col);
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            result.data[i][j] = data[i][j] + value;
        }
    }
    return result;
};

Matrix Matrix::operator*(double value){
    Matrix result(n_row, m_col);
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            result.data[i][j] = data[i][j] * value;
        }
    }
    return result;
};

int main(int argc, char* argv[]){
    Matrix m1("matrix.txt");

    Matrix m2(3, 2);
    m2.change(0, 0, 1.0);
    m2.change(0, 1, 2.0);
    m2.change(1, 0, 3.0);
    m2.change(1, 1, 4.0);
    m2.change(2, 0, 5.0);
    m2.change(2, 1, 6.0);

    Matrix m4(1, 1);
    m4.change(0, 0, 1.0);

    double ar1[6] {1., 2., 3., 4., 5., 6.};
    Matrix m3(2, 3, ar1);

    Matrix result = (m1*2.0 + m3)*m2;
    result.print_m();
    result.write_m("result.txt");

    Matrix tmp = result*m4;
    m4.get(5, 5);
    
    return 0;
}