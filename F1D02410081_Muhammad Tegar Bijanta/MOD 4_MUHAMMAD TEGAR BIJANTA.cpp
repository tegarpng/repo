#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//nama : Muhammad Tegar Bijanta
//nim  : F1D0241081

double f(double t) {
    return (4 * t - pow(t, 3)) * exp(pow(t, 2));
}

double forward_difference(double (*func)(double), double x, double h) {
    return (func(x + h) - func(x)) / h;
}

double central_difference(double (*func)(double), double x, double h) {
    return (func(x + h) - func(x - h)) / (2 * h);
}

double backward_difference(double (*func)(double), double x, double h) {
    return (func(x) - func(x - h)) / h;
}

double simpson_1_3(double (*func)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        cout << "Jumlah subinterval harus genap!" << endl;
        return 0;
    }

    double h = (b - a) / n;  
    double sum = func(a) + func(b);  
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)	sum += 2 * func(x);  
        else	sum += 4 * func(x);  
    }
    return (h / 3) * sum;  
}

double exact_derivative(double t) {
    return exp(pow(t, 2)) * (4 + 5 * pow(t, 2) - 2 * pow(t, 4));
}

int main() {
    double x = 0.5, h1 = 0.01, h2 = 0.001, h3 = 0.0001;
    double h_values[] = {0.01, 0.001, 0.0001};
    
    double forward1 = forward_difference(f, x, h1);
    double forward2 = forward_difference(f, x, h2);
    double forward3 = forward_difference(f, x, h3);
    
    double central1 = central_difference(f, x, h1);
    double central2 = central_difference(f, x, h2);
    double central3 = central_difference(f, x, h3);
    
    double backward1 = backward_difference(f, x, h1);
    double backward2 = backward_difference(f, x, h2);
    double backward3 = backward_difference(f, x, h3);
    
    double exact_value = exact_derivative(x);  
    cout << "1. Turunan pertama dari f(t) dengan selisih maju, dan terpusat pada x=0.5" << endl;
    cout << fixed << setprecision(6);
    cout << "-------------------------------------------------------------" << endl;
    cout << "| Metode                | h = 0.01 | h = 0.001 | h = 0.0001 |" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "| Forward Difference    | " << forward1 << " |  " << forward2 << " |  " << forward3 << "  |" << endl;
    cout << "| Central Difference    | " << central1 << " |  " << central2 << " |  " << central3 << "  |" << endl;
    cout << "| Backward Difference   | " << backward1 << " |  " << backward2 << " |  " << backward3 << "  |" << endl;
    cout << "-------------------------------------------------------------" << endl; 
    cout << "Perbandingan error ketiganya sebagai berikut." << endl;
    cout << "\n--------------------------------------------------------------------------------------" << endl;
    cout << "| Metode                | Error (h = 0.01) | Error (h = 0.001)  | Error (h = 0.0001) |" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "| Forward Difference    |\t" << fabs(forward1 - exact_value) << "   |\t" << fabs(forward2 - exact_value) << "\t|\t" << fabs(forward3 - exact_value) << "     |" << endl;
    cout << "| Central Difference    |\t" << fabs(central1 - exact_value) << "   |\t" << fabs(central2 - exact_value) << "\t|\t" << fabs(central3 - exact_value) << "     |" << endl;
    cout << "| Backward Difference   |\t" << fabs(backward1 - exact_value) << "   |\t" << fabs(backward2 - exact_value) << "\t|\t" << fabs(backward3 - exact_value) << "     |" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    
    cout << "\n2. Hasil dari perhitungan integral dengan Aturan Simpson 1/3 dari 0 sampai 1 sebagai berikut:" << endl;
    cout << fixed << setprecision(10);
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "|	h = 0.01	|	h = 0.001	|	h = 0.0001	|" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    for (double h : h_values) {
      int n = (1 - 0) / h;  
      if (n % 2 != 0) n++;  
      double result = simpson_1_3(f, 1, 0, n);  
      cout << "|\t" << h << "\t|\t" << n << "\t\t|\t" << result << "\t|" << endl;
    }
    cout << "-------------------------------------------------------------------------" << endl;
    
    return 0;
}
