//
// Created by Lê Ngọc Quốc Lịch on 06/12/2023.
//

#ifndef QR__ALGORITHM__MATRIX_H
#define QR__ALGORITHM__MATRIX_H
const short FOUR_CORNERS = -1;

const short EX_MATRIX = 10;
const short EX_BOUNDS = 20;
const short EX_EIGEN = 30;
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

class Matrix {
private:
    int length, width;
    std::vector<std::vector<long double>>numb;
public:
    Matrix(int length, int width);
    Matrix() = default;
    Matrix(const Matrix& m);
    ~Matrix() = default;

    int getLength() const;
    int getWidth() const;

    void printMatrix();
    long double getNumAt(int xPos, int yPos);
    void setNumAt(long double numb, int xPos, int yPos);


    Matrix operator-(const Matrix& m2) const;
};
Matrix Transpose(Matrix& m);
Matrix multiply(  Matrix&  m1, Matrix& m2);
Matrix I_matrix(int side);
vector<long double> x(Matrix& m, int k);
Matrix Householder(vector<long double>&m, const int side);
void QR_decomposition(Matrix& m);
Matrix symmetric_matrix_rand(short side);
vector<long double>Back_substitution(Matrix& m);
#endif //QR__ALGORITHM__MATRIX_H
