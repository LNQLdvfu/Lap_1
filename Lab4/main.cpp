#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
float calculate_integration_Simpson(float a, float b, int n);
float rectangle_integration(float a, float b, int n);
float trapezoidal_integration(float a,float b, int n);
float Yx(float x){ return powf(x,2) - cos(M_PI * x);}
float remainder_Simpson(float a, float b, int n);
float remainder_trapezoidal(float a, float b, int n);
int main()
{
    float a{}, b{};
    int n{};
    cout<<"Input n: ";
    cin>>n;
    cout<<"Input a,b: ";
    cin>>a>>b;

    cout<<calculate_integration_Simpson(a,b,n)<<endl;

    cout<<rectangle_integration(a,b,n)<<endl;
    cout<<trapezoidal_integration(a,b,n)<<endl;

    cout<<"remainder"<<endl;
    cout<<"remainder simpson: "<<remainder_Simpson(a,b,n)<<endl;
    cout<<"remainder trapezoidal : "<<remainder_trapezoidal(a,b,n)<<endl;

}
float calculate_integration_Simpson(float a, float b, int n) {
    float h = (b - a) / n;
    float X_O = Yx(a) + Yx(b);
    float X_1{};
    float X_2{};
    for(int i{}; i < n;i++)
    {
        float X = a + i*h;
        if(i % 2 == 0) {
            X_2 += Yx(X);
        } else
        {
            X_1 += Yx(X);
        }
    }
    return h*(X_O + 2*X_2 + 4*X_1) / 3;
}

float rectangle_integration(float a, float b, int n){
    float X_0{};
    float h = (b-a)/ n;
    for(int i{1}; i <= n; i++) {
        float X = a + i*h;
        float X_05 = X - 0.5*h;
        X_0 += Yx(X_05);
    }
    return h*X_0;
}

float trapezoidal_integration(float a,float b, int n) {
    float h = (b-a)/n;
    float X_0{};
    float X_1 = Yx(a) + Yx(b);
    for(int i{1};i < n - 1;i++) {
        float X_j = a + i*h;
        X_0 += Yx(X_j);
    }
    return h/2 *(X_1 + 2 * X_0);
}
float remainder_Simpson(float a, float b, int n) {
    float h = (b-a) / n;
    return  (b-a)* powf(M_PI,4) * powf(h,4);
}
float remainder_trapezoidal(float a, float b, int n)
{
    float h = (b-a)/n;
    return ((b-a) /12) * (2- powf(M_PI,2))* powf(h,2);
}