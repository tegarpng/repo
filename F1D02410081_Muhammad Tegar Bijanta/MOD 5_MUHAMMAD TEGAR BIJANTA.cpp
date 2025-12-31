#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//nama : Muhammad Tegar Bijanta
//nim  : F1D0241081

double result(double x, double y, double z) {
    return (0.25 * z - 64 * x * y); 
}
double zed(double x, double y, double z) {
    return z; 
}

int main() {
    cout << fixed << setprecision(8);
    double k1, k2, k3, k4, l1, l2, l3, l4;
    double b, h;
    cout << "Batas atas : ";cin >> b;
    cout << "Nilai h : ";cin >> h;
    int n = static_cast<int>(b / h);
    cout << "Banyak langkah : " << n << endl;
    double *x = new double[n + 1];
    double *y = new double[n + 1];
    double *z = new double[n + 1];
    x[0] = 0;
    y[0] = 1;
    z[0] = -8;
    for (int i = 1; i <= n; i++) {
        cout << endl;
        k1 = h * zed(x[i - 1], y[i - 1], z[i - 1]);
        l1 = h * result(x[i - 1], y[i - 1], z[i - 1]);
        k2 = h * zed(x[i - 1] + h / 2, y[i - 1] + k1 / 2, z[i - 1] + l1/ 2);
        l2 = h * result(x[i - 1] + h / 2, y[i - 1] + k1 / 2, z[i - 1] +l1 /2);
        k3 = h * zed(x[i - 1] + h / 2, y[i - 1] + k2 / 2, z[i - 1] + l2/ 2);
        l3 = h * result(x[i - 1] + h / 2, y[i - 1] + k2 / 2, z[i - 1] +l2 /2);
        k4 = h * zed(x[i - 1] + h, y[i - 1] + k3, z[i - 1] + l3);
        l4 = h * result(x[i - 1] + h, y[i - 1] + k3, z[i - 1] + l3);
        y[i] = y[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        z[i] = z[i - 1] + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
        x[i] = x[i - 1] + h;
        cout << "y" << i << " = " << y[i] << endl;
        cout << "z" << i << " = " << z[i] << endl;
    }
    delete[] x;
    delete[] y;
    delete[] z;
    return 0;
}