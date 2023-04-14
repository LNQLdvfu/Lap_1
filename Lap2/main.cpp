#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
void Creat_x(vector<float>& A, float a, float b, int n);
void caculate_y(vector<float>& m,vector<float>& A);
void Table_Differentiation(vector<vector<float>>&C, vector<float>&A);
float NEWTON_n(vector<vector<float>>&C, float x, int n );
float factorial(int n);
float remainder(const int n,const float a,const float b, const float x);
float fx(float d);
int main()
{
    const float a{0.1};
    const float b{0.6};
    float x{};
    cout<<"Enter x: ";
    cin>>x;

    int n{};
    cout<<"Input n: ";
    cin>>n;
    float y = (x - a)/((b-a)/n);
    vector<float>A(n);
    vector<float>B(n);
    vector<vector<float>>C(n, vector<float>(n));

    Creat_x(A,a,b,n);
    caculate_y(B,A);
    Table_Differentiation(C, B);

    cout<<"X = "<<endl;
    for(int i{}; i < n; i++){
        cout<<A[i]<<endl;
    }
//
    for(int i {}; i < n;i++)
    {
        for(int j{}; j < n; j++)
        {
            cout<<C[i][j]<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<"fx = "<<fx(x)<<endl;
    cout<<"F_Newton: "<<NEWTON_n(C,y,n)<<endl;
    cout<<"Remainder: "<<remainder(n,a,b,y)<<endl;
    cout<<"Delta: "<<abs(fx(x) - NEWTON_n(C,y,n));
}

void Creat_x(vector<float>& A, float a, float b, int n){
    float h = (b -a ) / n;
    for(int i{}; i < n; ++i)
    {
        A[i] = a + h*i;
    }
}

void caculate_y(vector<float>& m,vector<float>& A){
    for(int i{}; i < m.size(); i++)
    {
        m[i] = pow(A[i],2) - cos(M_PI * A[i]);
    }
}

void Table_Differentiation(vector<vector<float>>&C, vector<float>&A){
    for(int i{}; i < A.size();i++){
        C[0][i] = A[i];
    }
    int B = A.size();
    for(int i{1}; i < A.size();i++){
        B--;
        for(int j{}; j < B; j++)
        {
            C[i][j]= C[i-1][j+1] - C[i-1][j];
        }
    }
}

float NEWTON_n(vector<vector<float>>&C, float x, int n ){
    float Ni = C[0][0];
    for(int i{1};i < n; i++)
    {
        float px{1};
        for(int j{};j <= i -1;j++){

            px =px * (x-j);
        }
        Ni += C[i][0]*px*(1 / factorial(i));
    }
    return Ni;
}

float factorial(int n){

    if (n > 0) {
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}

float remainder(const int n,const float a,const float b, const float x){
    float m{};
    if((n+1) %2 == 0){
        m = pow(M_PI,n+1) * cos(M_PI * x);
    }
    else{
        m = pow(M_PI,n+1)*sin(M_PI * x);
    }
    return ((abs(m) / factorial(n + 1)) * pow(( b - a),n+1));
}

float fx(float d){
    return  pow(d,2) - cos(M_PI * d);
}