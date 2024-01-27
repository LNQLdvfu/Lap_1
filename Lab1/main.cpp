#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void gaussianElimination(vector<vector<double>>& A, int n, vector<double>& x) {
    vector<int> NROW(n); // Array to keep track of row interchanges

    // Step 1: Initialize NROW and check for unique solution
    for (int i = 0; i < n; ++i) {
        double maxVal = 0.0;
        for (int j = 0; j < n; ++j) {
            maxVal = max(maxVal, fabs(A[i][j]));
        }

        if (maxVal == 0) {
            cout << "No unique solution exists." << endl;
            return;
        }

        NROW[i] = i;
    }

    // Step 2: Gaussian elimination with partial pivoting
    for (int i = 0; i < n; ++i) {
        // Step 3-5
        int p = i;
        for (int j = i; j < n; ++j) {
            if (fabs(A[NROW[j]][i] / fabs(A[NROW[j]][i])) > fabs(A[NROW[p]][i] / fabs(A[NROW[p]][i]))) {
                p = j;
            }
        }

        // Step 4
        if (A[NROW[p]][i] == 0) {
            cout << "No unique solution exists." << endl;
            return;
        }

        // Step 5
        if (NROW[i] != NROW[p]) {
            swap(NROW[i], NROW[p]);
        }

        // Step 6-8
        for (int j = i + 1; j < n; ++j) {
            double m = A[NROW[j]][i] / A[NROW[i]][i];
            for (int k = i; k <= n; ++k) {
                A[NROW[j]][k] -= m * A[NROW[i]][k];
            }
        }
    }

    // Step 9
    if (A[NROW[n - 1]][n - 1] == 0) {
        cout << "No unique solution exists." << endl;
        return;
    }

    // Step 10: Back substitution
    x[n - 1] = A[NROW[n - 1]][n] / A[NROW[n - 1]][n - 1];

    // Step 11
    for (int i = n - 2; i >= 0; --i) {
        double sum = A[NROW[i]][n];
        for (int j = i + 1; j < n; ++j) {
            sum -= A[NROW[i]][j] * x[j];
        }
        x[i] = sum / A[NROW[i]][i];
    }
}

double infinityNorm(const vector<double>& v) {
    double maxVal = 0.0;
    for (double val : v) {
        maxVal = max(maxVal, fabs(val));
    }
    return maxVal;
}

int main() {
    int n, N, t;
    double c,d;
    double TOL;

    // Input: n, A, b, N, TOL, t
    cout << "Enter the number of equations and unknowns (n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n+1));
    vector<double> b(n);
    vector<double> x(n);
    vector<double> xx(n);
    vector<double>z(n);
    vector<double> r(n);
    vector<double> y(n);

    cout << "Enter the entries of matrix A:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> A[i][j];
        }
    }

    cout << "Enter the entries of vector b:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    cout << "Enter the maximum number of iterations (N): ";
    cin >> N;

    cout << "Enter the tolerance (TOL): ";
    cin >> TOL;

    cout << "Enter the number of digits of precision (t): ";
    cin >> t;

    // Step 0: Gaussian elimination
    gaussianElimination(A, n, x);
    for(auto& X:x){
        cout<<X<< " ";
    }

    cout<<endl;

    int k = 1;
    double COND = 0.0;

    while (k <= N) {
        // Step 3: Calculate r
        for (int i = 0; i < n; ++i) {
            r[i] = b[i];
            for (int j = 0; j < n; ++j) {
                r[i] -= A[i][j] * x[j];
            }
        }
        for(int i{}; i < n; i++){
            for(int j{n}; j <= n ; j++ )
                A[i][j] = r[i];
        }
        // Step 4: Solve the linear system Ay = r by Gaussian elimination
        gaussianElimination(A, n, y);

        // Step 5: Update xx
        for (int i = 0; i < n; ++i) {
            xx[i] =x[i] +  y[i];
        }

        // Step 6: Calculate COND on the first iteration
        if (k == 1) {
            COND = (infinityNorm(y) / infinityNorm(xx)) * pow(10, t);
        }
        for(int i{};i < n; i++) {
            z[i] = x[i] -xx[i];
        }
        // Step 7: Check convergence
        if (infinityNorm(z) <= TOL) {
            cout << "Approximation (xx): ";
            for (double val : xx) {
                cout << val << " ";
            }
            cout << endl;
            cout << "COND: " << COND << endl;
            cout << "The procedure was successful." << endl;
            return 0; // Stop
        }

        // Step 8: Increment iteration count
        ++k;

        // Step 9: Update x for the next iteration
        for (int i = 0; i < n; ++i) {
            x[i] = xx[i];
        }
    }

    // Step 10: Output if maximum iterations exceeded
    cout << "Maximum number of iterations exceeded." << endl;
    cout << "COND: " << COND << endl;

    return 0;
}