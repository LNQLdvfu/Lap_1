#include <iostream>
#include <vector>

using namespace std;
void LU_method(vector<vector<double>>&A, vector<vector<double>>&L, vector<vector<double>>&U);
void calculate_y(vector<vector<double>>& L, vector<double>& b, vector<double>& y);
void calculate_x(vector<vector<double>>& U, vector<double>& y, vector<double>& x, int &n);
vector<vector<double>> Creat_L(vector<vector<double>>& A) {
    size_t n{A.size()};
    for(int i{}; i < n; i++) {
        A[i][i] = 1;
    }
    return A;
}


int main(){
    int n{};
    cout<<"enter n: ";
    cin>>n;

    vector<vector<double>>A(n,vector<double>(n,0));
    cout<<"enter element of A"<<endl;
    for(int i{} ; i < n; i++) {
        for(int j{}; j < n; j++) {
            cin >> A[i][j];
        }
    }
    vector<vector<double>>L(n,vector<double>(n,0));
    vector<vector<double>>U(n,vector<double>(n,0));
    Creat_L(L);
    LU_method(A,L,U);

    cout<<"Matrix L: "<<endl;
    for(int i{} ; i < n; i++) {
        for(int j{}; j < n; j++) {
            cout<<L[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
    cout<<"Matrix U: "<<endl;
    for(int i{} ; i < n; i++) {
        for(int j{}; j < n; j++) {
            cout<<U[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;

    vector<double>b(n);


    cout<<"Enter b:"<<endl;
    for(int i{}; i < n; i ++) {
        cin>>b[i];
    }
    vector<double>x(n);
    vector<double>y(n);

    calculate_y(L,b,y);
    calculate_x(U,y,x,n);
    cout<<"solution for y:"<<endl;
    for(int i{}; i < n; i++) {
        cout<<y[i] <<" ";
    }
    cout<<endl<<"solution for x: "<<endl;

    for(int i{}; i < n; i++) {
        cout<<x[i] <<" ";
    }

}

void LU_method(vector<vector<double>>&A, vector<vector<double>>&L, vector<vector<double>>&U) {
    const size_t n{A.size()};
    U[0][0] = A[0][0] / L[0][0];
    if(L[0][0] * U[0][0] == 0)
    {
        cout<<"Factorization impossible";
        return;
    }

    for(size_t i{1}; i < n; i++) {
        U[0][i] = A[0][i] / L[0][0];
        L[i][0] = A[i][0] / U[0][0];
    }

    for(size_t i{1}; i < n - 1 ; i++)
    {
        double L_ii_U_ii{};
        for(size_t k{0}; k <= i - 1; k++)
        {
            L_ii_U_ii +=   L[i][k]*U[k][i];
        }

        U[i][i] = (A[i][i] - L_ii_U_ii) / L[i][i];

        if(L[i][i]*U[i][i] == 0 )
        {
            cout<<"Factorization impossible";
            return;
        }

        for(size_t  j{i + 1}; j < n; j++)
        {
            double l_ik_u_kj{};
            double l_jk_u_ki{};
            for(size_t k{0}; k <= i - 1; k++)
            {
                l_ik_u_kj += L[i][k]*U[k][j];
                l_jk_u_ki += L[j][k]*U[k][i];
            }
            U[i][j] = 1/L[i][i] * (A[i][j] - l_ik_u_kj);
            L[j][i] = 1/U[i][i] * (A[j][i] - l_jk_u_ki);
        }

    }
    double L_nn_U_nn{};
    for(int k{}; k < n; k++) {
        L_nn_U_nn += L[n-1][k]*U[k][n-1];
    }
    U[n-1][n-1] = A[n-1][n-1] -L_nn_U_nn;


}

void calculate_y(vector<vector<double>>& L, vector<double>& b, vector<double>& y)
{
     y[0] = b[0] / L[0][0];
    for(int i{1}; i < L.size(); i++) {
        double L_ij_yj{};
        for(int j{}; j <= i - 1; j ++) {
            L_ij_yj += L[i][j]*y[j];
        }
        y[i] = 1/L[i][i] *(b[i] - L_ij_yj);
    }

}

void calculate_x(vector<vector<double>>& U, vector<double>& y, vector<double>& x, int &n){

    x[n-1] = y[n-1] / U[n-1][n-1];
    for(int i{n - 2}; i >= 0; i--) {
        double U_ij_xj{};
        for(int j{i+1}; j <= n; j ++) {
            U_ij_xj += U[i][j]*x[j];
        }
        x[i] =1/ U[i][i] * (y[i] - U_ij_xj)  ;
    }
}