#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
void Cholesky_method(vector<vector<double>>& A, vector<vector<double>>& L, int& n);
void symmetry_L(vector<vector<double>>& L, vector<vector<double>>& U, int& n);
void X_calculating(vector<vector<double>>&L, vector<double>&b, vector<double>&x, int &n);

int main() {
    int n{};
    cout<< "enter n: ";
    cin>>n;
    cout<<"enter Matrix A: "<<endl;
    vector<vector<double>>A(n, vector<double>(n));
    for(int i{}; i < n; i++) {
        for(int j{}; j < n; j ++) {
            cin>> A[i][j];
        }
    }

    vector<vector<double>>L(n, vector<double>(n));
    Cholesky_method(A, L, n);
    cout<<endl;

    for(int i{}; i < n; i++) {
        for(int j{}; j < n; j ++) {
            cout<< L[i][j]<<" ";
        }
        cout<< endl;
    }

    vector<vector<double>>U(n, vector<double>(n));
    symmetry_L(L, U, n);
    cout<<endl;

    for(int i{}; i < n; i++) {
        for(int j{}; j < n; j ++) {
            cout<< U[i][j]<<" ";
        }
        cout<< endl;
    }

    vector<double>b(n);
    cout<<"enter b: "<<endl;
    for(int i{}; i < n; i ++) {
        cin>>b[i];
    }

    vector<double>x(n);
    X_calculating(L,b,x,n);
    cout<<endl;
    cout<<"solution for x:"<<endl;
    for(auto& a:x){
        cout<<a<<" ";
    }

}

void Cholesky_method(vector<vector<double>>& A, vector<vector<double>>& L, int& n) {
    L[0][0] = sqrt(A[0][0]);
    for(int j{1}; j < n;j++) {
        L[j][0] = A[j][0] / L[0][0];
    }

    for(int i{1}; i < n -1; i++) {
        double L_ik{};
        for(int k{0}; k <= i - 1; k++) {
            L_ik += pow(L[i][k],2);
        }
        L[i][i] = sqrt(A[i][i] - L_ik);
       for(int j{i+1}; j < n;j ++) {
           double L_jk_L_ik{};
           for(int k{0}; k <= i - 1; k++) {
               L_jk_L_ik += L[j][k]*L[i][k];
           }
           L[j][i] = (A[j][i] -L_jk_L_ik) / L[i][i];
       }
    }
    double L_nk{};
    for(int k{}; k < n - 1; k++) {
        L_nk += pow(L[n-1][k],2);
    }
    L[n-1][n-1] = sqrt(A[n-1][n-1] - L_nk);
}

void symmetry_L(vector<vector<double>>& L, vector<vector<double>>& U, int& n) {
    for(int i{0}; i < n; i ++) {
        for(int j{i+1}; j < n; j ++) {
            U[i][j] = L[j][i];
        }
        U[i][i] = L[i][i];
    }
}

void X_calculating(vector<vector<double>>&L, vector<double>&b, vector<double>&x, int &n) {
    vector<double>y(n);
    y[0] = b[0] / L[0][0];
    for(int i{1}; i < n; i++) {
        double L_ij_yj{};
        for(int j{}; j <= i - 1; j++) {
            L_ij_yj += L[i][j] * y[j];
        }
        y[i] = (b[i] -L_ij_yj) / L[i][i];
    }
    x[n-1] = y[n-1] / L[n-1][n-1];
    for(int i{n-2}; i >=0 ; i--) {
        double L_ji_xj{};
        for(int j{i+1}; j < n; j++) {
            L_ji_xj += L[j][i] * x[j];
        }
        x[i] = (y[i] - L_ji_xj) / L[i][i];
    }


}