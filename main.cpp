#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class Matrix {
    int columns;
    int rows;
    int** data;
public:
    Matrix();
    Matrix(const int& columns, const int& rows);
    Matrix(const Matrix& M);
    ~Matrix();
    void print();
    void randomize();
    int& accessElement(const int& row, const int& column);
    Matrix operator+(const Matrix& M) const;
    Matrix operator-(const Matrix& M) const;
    Matrix operator*(const Matrix& M) const;
    Matrix operator*(const int& scalar) const;
};

Matrix::Matrix() {
    cout << "Please enter the number of columns: ";
    cin >> columns;
    cout << "Please enter the number of rows: ";
    cin >> rows;

    data = new int*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[columns];
    }
}

Matrix::Matrix(const int& columns, const int& rows) : columns(columns), rows(rows) {
    data = new int*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[columns];
    }
}

Matrix::Matrix(const Matrix& M) {
    columns = M.columns;
    rows = M.rows;

    data = new int*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[columns];
        for (int j = 0; j < columns; j++) {
            data[i][j] = M.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::randomize() {
    srand(time(nullptr));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data[i][j] = rand() % 10;
        }
    }
}

int& Matrix::accessElement(const int& row, const int& column) {
    return data[row][column];
}

Matrix Matrix::operator+(const Matrix& M) const {
    if (rows != M.rows || columns != M.columns) {
        throw std::invalid_argument("Matrix dimensions must match!");
    }
    Matrix result(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result.data[i][j] = data[i][j] + M.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& M) const {
    if (rows != M.rows || columns != M.columns) {
        throw std::invalid_argument("Matrix dimensions must match!");
    }
    Matrix result(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result.data[i][j] = data[i][j] - M.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& M) const {
    if (columns != M.rows) {
        throw std::invalid_argument("Mismatched dimensions for matrix multiplication!");
    }
    Matrix result(rows, M.columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < M.columns; ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < columns; ++k) {
                result.data[i][j] += data[i][k] * M.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(const int& scalar) const {
    Matrix result(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}


int main()
{
    Matrix matrixA;
    matrixA.randomize();
    cout << "Matrix A:" << endl;
    matrixA.print();
    Matrix matrixB(3, 3);
    matrixB.randomize();
    cout << "Matrix B:" << endl;
    matrixB.print();
    cout << "Matrix A + Matrix B:" << endl;
    Matrix resultAdd = matrixA + matrixB;
    resultAdd.print();
    cout << "Matrix A - Matrix B:" << endl;
    Matrix resultSubtract = matrixA - matrixB;
    resultSubtract.print();
    cout << "Matrix A * Matrix B:" << endl;
    Matrix resultMultiply = matrixA * matrixB;
    resultMultiply.print();
    cout << "Matrix A * 2:" << endl;
    Matrix resultScalarMultiply = matrixA * 2;
    resultScalarMultiply.print();
}
