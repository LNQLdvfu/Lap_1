#include <iostream>
#include "Matrix.h"
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;


Matrix:: Matrix(int length, int width){
    this->length = length;
    this->width = width;
    std::vector<std::vector< long double>> A(length, std::vector<long double>(width));
    numb = A;
}
Matrix::Matrix(const Matrix& m):length(m.length), width(m.width) , numb(m.numb){};


int  Matrix::getLength() const {
    return this->length;
}
int Matrix::getWidth() const {
    return this->width;
}

void Matrix::printMatrix() {

    cout << "[";

    for(int i = 0; i < length; i++)
    {
        if(i > 0)
            cout << " ";

        cout << "[";

        for(int j = 0; j < width; j++)
        {
            cout << numb[i][j];

            if(j < width - 1)
                cout << " ";
        }

        cout << "]";

        if(i < length - 1)
            cout << endl;
    }

    cout << "]" << endl;
}
long double Matrix::getNumAt(int xPos, int yPos){
    if(xPos < length && xPos >=0 && yPos < width && yPos >=0) {
        return numb[xPos][yPos];
    }
    else
        throw EX_BOUNDS;
}
void Matrix::setNumAt(long double numb, int xPos, int yPos) {
    if(xPos < length && xPos >=0 && yPos < width && yPos >=0) {
        this->numb[xPos][yPos] = numb;
    } else
        throw EX_BOUNDS;
}

Matrix Transpose(Matrix& m) {
    Matrix n(m.getWidth(), m.getLength());
    for(int i{}; i < m.getWidth();i++) {
        for(int j{}; j < m.getLength(); j++) {
            n.setNumAt(m.getNumAt(i,j),j ,i);
        }
    }
    return n;
}
Matrix Matrix::operator-(const Matrix& m2) const
{
    if (length != m2.length || width != m2.width) {
        throw std::invalid_argument("Matrix dimensions do not match for subtraction");
    }

    Matrix result(length, width);

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            result.numb[i][j] = numb[i][j] - m2.numb[i][j];
        }
    }

    return result;
}
//
Matrix multiply(  Matrix&  m1, Matrix& m2) {
    int a{m1.getWidth()};
    int b{m2.getLength()};
    if(a == b)
    {
        Matrix m (m1.getLength(), m2.getWidth());
        long double temSum{};

        for(int i {}; i < m1.getLength(); ++i) {
            for(int j{}; j < m2.getWidth(); ++j) {
                for(int t{}; t < m1.getWidth(); ++t)
                    temSum += m1.getNumAt(i, t) * m2.getNumAt(t,j);
                m.setNumAt(temSum, i,j);
                temSum = 0;
            }
        }
        return m;
    } else
        throw EX_MATRIX;


}
Matrix I_matrix(int side) {
    Matrix m (side,side);

    for(int i{}; i < side; i++) {
        for(int j{}; j < side; j++) {
            m.setNumAt(((i == j) ? 1 : 0) ,i ,j);
        }
    }
    return m;
}
vector<long double> x(Matrix& m, int k){
    vector<long double> X(m.getLength(), 0) ;
    long double sum{};
    for(int i{k}; i < m.getLength();i++ ) {
        for(int j{k}; j <=k;j++) {
            X[i] = m.getNumAt(i,j);
            sum += pow(X[i],2) ;
        }
    }
    long double norm_x = sqrt(sum);
    X[k] = X[k] - norm_x;
    double Sum_x{};
    for(int i{}; i < m.getLength(); i ++) {
        Sum_x += pow(X[i],2);
    }
    long double Sum_xx{sqrt(Sum_x)};
    for(int i{}; i < m.getLength();i++){
        X[i] /= Sum_xx;
    }

    return X;
}
Matrix Householder(vector<long double>&m, const int side) {
    Matrix m1(side, side);

    for(int i{} ; i<side;i++ ) {
        for(int j{}; j<=0 ;j++ )
            m1.setNumAt(m[i],i,j);
    }
    Matrix mT = Transpose(m1);
    Matrix a = multiply(m1,mT);

    for(int i{}; i < side; i++) {
        for(int j{}; j < side; j++)
            a.setNumAt(2*a.getNumAt(i,j),i,j);
    }

//    for(int i{}; i < side; i ++) {
//        for(int j{i};  ;) {
//            if(i == j)
//                a.setNumAt(1 - a.getNumAt(i,j),i,j);
//        }
//    }
    Matrix C = I_matrix(side) - a;
    return C;
}
void QR_decomposition(Matrix& m) {
    int k{0};
    vector<long double> X = x(m, k);

    while(k < m.getLength() -1) {
        cout<<"vector X:"<<k<<endl;
        for(auto b : X) {
            cout<<b<< " ";
        }
        cout<<endl;
        Matrix a = Householder(X,m.getLength());
        cout<<" Matrix R"<<k<<endl;
        a.printMatrix();

        cout<<"Matrix A"<<k<<endl;
        Matrix b = multiply(a, m);
        m = b;
        k++;
        X=x(b,k);

        b.printMatrix();
    }
}

Matrix symmetric_matrix_rand(short side)
{
    Matrix m(side, side);
    minstd_rand random(system_clock::now().time_since_epoch().count());

    for(int i = 0; i < side; i++)
        for(int j = 0; j <= i; j++)
            m.setNumAt((random() % 9) + 1, j, i);

    for(int i = 1; i < side; i++)
        for(int j = i - 1; j >= 0; j--)
            m.setNumAt(m.getNumAt(j, i), i, j);

    return m;
}

vector<long double>Back_substitution(Matrix& m) {
    const int n{m.getLength()};
    const int k{m.getWidth()};
    vector<long double>X(n);
    X[n-1] = m.getNumAt(n-1,k-1)/m.getNumAt(n-1,n-1);
    for(int i{n-2};i >=0;i--) {
        long double A{};
        for(int j{i +1}; j < n; j++){
            A += m.getNumAt(i,j) * X[j];
        }
        X[i] = (m.getNumAt(i,n) - A) / m.getNumAt(i,i);
    }
    return X;
}