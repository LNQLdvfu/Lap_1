#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void SOR(vector<vector<double>>&A, vector<double>& b, vector<double>&XO, vector<double>&x,
                  double &TOL, const int& N, int& n, int&Index, double& omega);


int main() {
    int n{};
    cout<<"enter n: ";
    cin>>n;
    const int N{100};
    cout<<endl;
    cout<<"enter A:"<<endl;

    vector<vector<double>>A(n, vector<double>(n));
    for(int i{}; i < n; i++) {
        for( int j{}; j < n; j++)
        {
            cin>>A[i][j];
        }
    }
    vector<double>b(n);
    cout<<endl;
    cout<<"Enter b:"<<endl;
    for(int i{}; i < n; i++) {
        cin>>b[i];
    }

    cout<<endl;
    cout<<"enter X_0:" <<endl;
    vector<double>X0(n);
    for(int i{}; i < n; i++) {
        cin>>X0[i];
    }

    cout<<endl;
    double TOL{};
    cout<<"Enter tolerance: ";
    cin>>TOL;
    cout<<endl;

    double omega{};
    cout<<"enter omega: ";
    cin>>omega;

    int Index{};
    vector<double>x(n);

    SOR(A,b,X0,x,TOL,N,n, Index, omega);
    cout<<"Index is: "<<Index<<endl;
    for(auto & a: x) {
        cout<<a<<" ";
    }






}


void SOR(vector<vector<double>>&A, vector<double>& b, vector<double>&XO,
                  vector<double>&x,  double &TOL, const int& N, int& n, int&Index, double & omega) {
    int k{1};
    while(k <= N) {
        vector<double>x_X0(n);
        for(int i{}; i < n ; i++)
        {
            double A_ij_X_j{};
            double A_ij_X0j{};
            for(int j{}; j <= i - 1; j++)
            {
                A_ij_X_j += A[i][j] * x[j];
            }
            for(int j{i+1}; j < n; j++)
            {
                A_ij_X0j += A[i][j] * XO[j];
            }
            x[i] = 1 / A[i][i] *( omega *(b[i] - A_ij_X_j - A_ij_X0j)) + (1 - omega)*XO[i];
            x_X0[i] = abs(x[i] - XO[i]);
        }
        auto maxElement = std::max_element(x_X0.begin(), x_X0.end());
        if(*maxElement < TOL) {
            return;
        }
        k++;
        Index = k;
        for(int i{}; i < n; i++) {
            XO[i] = x[i];
        }

    }
}