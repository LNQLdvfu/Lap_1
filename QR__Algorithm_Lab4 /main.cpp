#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace  std;
int main() {
    int length{}, width{};
    cout<<"enter your length and width: ";
    cin>> length>>width;

    cout<<endl;

    vector<vector<long double>>A(length, vector<long double>(width));

    cout<<"enter A|b: "<<endl;
    for(int i{}; i < length;i ++) {
        for(int j{};j < width; j++)
            cin>>A[i][j];
    }
    Matrix B (length, width);
    for(int i{}; i < length; i++) {
        for(int j{}; j < width;j++) {
            B.setNumAt(A[i][j], i,j);
        }
    }
    QR_decomposition(B);
    cout<<endl;
    cout<<"solution: ";
    vector<long double> X{Back_substitution(B)};
    for(auto x: X) {
        cout<<x<< " ";
    }

//      Matrix B{symmetric_matrix_rand(4)};
//      B.printMatrix();
//      QR_decomposition(B);
}

