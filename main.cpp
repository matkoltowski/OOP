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
    Matrix operator|(const Matrix& M) const;
    Matrix operator/(const Matrix& M) const;
    Matrix& operator*=(const Matrix& M);
    Matrix& operator+=(const Matrix& M);
    Matrix& operator-=(const Matrix& M);
    Matrix& operator|=(const Matrix& M);
    Matrix& operator/=(const Matrix& M);
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
        data[i] = new int[columns]();
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

Matrix Matrix::operator|(const Matrix& M) const {
    if (rows != M.rows) {
        throw std::invalid_argument("Rows must be the same to concatenate.");
    }
    Matrix result(rows, columns + M.columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result.data[i][j] = data[i][j];
        }
        for (int j = 0; j < M.columns; ++j) {
            result.data[i][columns + j] = M.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator/(const Matrix& M) const {
    if (columns != M.columns) {
        throw std::invalid_argument("Columns must be the same to concatenate.");
    }
    Matrix result(rows + M.rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result.data[i][j] = data[i][j];
        }
    }
    for (int i = 0; i < M.rows; ++i) {
        result.data[rows + i] = new int[columns];
        for (int j = 0; j < columns; ++j) {
            result.data[rows + i][j] = M.data[i][j];
        }
    }
    return result;
}

Matrix& Matrix::operator*=(const Matrix& M) {
    if (this->columns != M.rows) {
        throw std::invalid_argument("Mismatched dimensions for matrix multiplication!");
    }
    Matrix tmp = *this * M;

    for (int i = 0; i < this->rows; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;

    this->rows = tmp.rows;
    this->columns = tmp.columns;
    this->data = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->data[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->data[i][j] = tmp.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& M) {
    if (this->rows != M.rows || this->columns != M.columns) {
        throw std::invalid_argument("Matrix dimensions must match to add!");
    }
    Matrix tmp = *this + M;

    for (int i = 0; i < this->rows; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;

    this->rows = tmp.rows;
    this->columns = tmp.columns;
    this->data = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->data[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->data[i][j] = tmp.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& M) {
    Matrix temp = *this - M;

    for (int i = 0; i < rows; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;

    rows = temp.rows;
    columns = temp.columns;
    data = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new int[columns];
        for (int j = 0; j < columns; ++j) {
            data[i][j] = temp.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator|=(const Matrix& M) {
    if (rows != M.rows) {
        cout << "Cannot apply operator |= to matrices of different heights." << endl;
        return *this;
    } else {
        int newColumns = columns + M.columns;
        Matrix result(newColumns, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result.data[i][j] = data[i][j];
            }
            for (int j = 0; j < M.columns; ++j) {
                result.data[i][columns + j] = M.data[i][j];
            }
        }
        *this = result;
        return *this;
    }
}

Matrix& Matrix::operator/=(const Matrix& M) {
    if (columns != M.columns) {
        cout << "Cannot apply operator /= to matrices of different widths." << endl;
        return *this;
    } else {
        int newRows = rows + M.rows;
        Matrix result(columns, newRows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result.data[i][j] = data[i][j];
            }
        }
        for (int i = 0; i < M.rows; ++i) {
            for (int j = 0; j < M.columns; ++j) {
                result.data[rows + i][j] = M.data[i][j];
            }
        }
        *this = result;
        return *this;
    }
}


int main()
{
    Matrix matrixA;
    matrixA.randomize();
    cout << "Matrix A:" << endl;
    matrixA.print();
    Matrix matrixB(5, 5);
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
    cout << "Matrix A | Matrix B (concatenate columns):" << endl;
    Matrix resultConcatColumns = matrixA | matrixB;
    resultConcatColumns.print();
    cout << "Matrix A / Matrix B (concatenate rows):" << endl;
    Matrix resultConcatRows = matrixA / matrixB;
    resultConcatRows.print();
    matrixA += matrixB;
    cout << "Matrix A after A += B:" << endl;
    matrixA.print();
    matrixA -= matrixB;
    cout << "Matrix A after A -= B:" << endl;
    matrixA.print();
    matrixA *= matrixB;
    cout << "Matrix A after A *= B:" << endl;
    matrixA.print();
    matrixA |= matrixB;
    cout << "Matrix A after A |= B:" << endl;
    matrixA.print();
    matrixA /= matrixB;
    cout << "Matrix A after A /= B:" << endl;
    matrixA.print();
}
