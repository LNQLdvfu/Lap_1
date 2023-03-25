#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<time.h>

using namespace std;

void randomize_x(float a, float b, vector<float>& c);
void caculate_y(vector<float>& m,vector<float>& d);
float caculate_Ln(vector<float> &a, vector<float> &b, float xp);
float fx(float d);
float caculate_delta(float a, float b) {return abs(a - b);}
float caculate_thelta(float a, float b) {return (abs(a - b) / abs(b)) * 100;}
float remainder(const int n,const float a, const float b,const float x);
float factorial(int n);

int main(){

    const float a{0.1},b{0.6};


    float xp{};
    cout<<"Enput the value needing to caculate: ";
    cin>>xp;
    vector<float>container;
    bool u{true};
    vector<vector<float>>pp;
    vector<float>delta;
    vector<float>thelta;
    vector<float>remainder_1;
    while (u){
        cout<<"Enter n: ";
        int n;
        cin>>n;
        container.push_back(n);
        char ss;
        cout<<"Do you want to extra n(y/n): ";
        cin>>ss;
        if(ss == 'y')
            u = true;
        else
            u = false;

        vector<float>X_i(n);
        vector<float>Y_i(n);

        randomize_x(a,b,X_i);
        caculate_y(Y_i,X_i);
        vector<float>overall;
        overall.push_back(caculate_Ln(X_i,Y_i,xp));
        float m = overall.front();
        overall.push_back(caculate_thelta(m,fx(xp)));
        thelta.push_back(caculate_thelta(m,fx(xp)));
        overall.push_back(caculate_delta(m,fx(xp)));
        delta.push_back(caculate_delta(m,fx(xp)));
        overall.push_back(remainder(n,a,b,xp));
        remainder_1.push_back(remainder(n,a,b,xp));
        pp.push_back(overall);
    }



    for(int i{}; i < pp.size(); ++i){
        cout<<"n = "<<container[i]<<"| ";
        for(int j{}; j < pp[i].size(); ++j){
            cout<<pp[i][j]<< " ";
        }
        cout<<endl;
    }
    cout<<"thelta"<<endl;
    for(float x: thelta){
        cout<<x<<endl;
    }

    cout<<"delta"<<endl;
    for(float x: delta){
        cout<<x<<endl;
    }

    cout<<"remainder"<<endl;
    for(float x: remainder_1){
        cout<<x<<endl;
    }


}

void randomize_x(float a, float b, vector<float>& c){
    srand(time(0));
    for(int i{}; i < c.size(); i++)
    {
        c[i] = a + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (b-a)));
    }
}


void caculate_y(vector<float>& m,vector<float>& d){
    for(int i{}; i < m.size(); i++)
    {
        m[i] = pow(d[i],2) - cos(M_PI * d[i]);
    }
}

float fx(float d){
    return  pow(d,2) - cos(M_PI * d);
}

float caculate_Ln(vector<float> &a, vector<float> &b, float xp){
    float Ln{0};
    if(a.size() == b.size())
    {
        for(int i{}; i < b.size(); i++)
        {
            float Sn{1};
            for(int j{}; j < a.size(); j++)
            {
                if(i != j) {
                    Sn = Sn * (xp - a[j]) / (a[i] - a[j]);
                }
            }
            Ln = Ln + Sn*b[i];
        }
    }
    return Ln;
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

float factorial(int n){

    if (n > 0) {
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}