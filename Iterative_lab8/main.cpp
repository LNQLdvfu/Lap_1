#include <iostream>
#include <vector>
#include <cmath>

void powerIteration(const std::vector<std::vector<double>>& A, std::vector<double>& x, double TOL, int N) {
    int n = x.size();
    int k = 1;
    int p = 0;
    for (int i = 0; i < n; ++i) {
        if (std::abs(x[i]) > std::abs(x[p])) {
            p = i;
        }
    }

    double x_p = x[p];
    for (int i = 0; i < n; ++i) {
        x[i] /= x_p;
    }

    while (k <= N) {


        std::vector<double> y(n, 0.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                y[i] += A[i][j] * x[j];
            }
        }

        double mu = y[p];

        p = 0;
        for (int i = 0; i < n; ++i) {
            if (std::abs(y[i]) > std::abs(y[p])) {
                p = i;
            }
        }

        // Step 8
        if (y[p] == 0) {
            std::cout << "Eigenvalue: 0, Eigenvector: ";
            for (int i = 0; i < n; ++i) {
                std::cout << x[i] << " ";
            }
            std::cout << "\nA has the eigenvalue 0, select a new vector x and restart." << std::endl;
            return;
        }

        double ERR = 0.0;
        for (int i = 0; i < n; ++i) {
            ERR = std::max(ERR, std::abs(x[i] - y[i] / y[p]));
            x[i] = y[i] / y[p];
        }

        if (ERR < TOL) {
            std::cout << "Eigenvalue: " << mu <<std::endl<< "Eigenvector: ";
            for (int i = 0; i < n; ++i) {
                std::cout << x[i] << " ";
            }
            std::cout << "\nProcedure was successful." << std::endl;
            return;
        }

        // Step 11
        ++k;
    }

    // Step 12
    std::cout << "The maximum number of iterations exceeded." << std::endl;
}

int main() {
    // Example usage
    int n{};
    std::cout<<"Enter dimension n: ";
    std::cin>>n;
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::cout<<"Enter A:" <<std::endl;
    for(int i{}; i < n;i ++) {
        for(int j{};j < n; j++) {
            std::cin>>A[i][j];
        }
    }
    double TOL{};
    std::cout<< "Enter tolerance: ";
    std::cin>>TOL;

    std::vector<double>x(n);
    std::cout<<"Enter x: "<<std::endl;
    for(auto& a: x) {
        std::cin>> a;
    }
    const int N = 100;

    powerIteration(A, x, TOL, N);

    return 0;
}
