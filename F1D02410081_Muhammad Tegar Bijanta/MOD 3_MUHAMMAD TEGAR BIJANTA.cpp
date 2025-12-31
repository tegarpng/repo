#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//nama : Muhammad Tegar Bijanta
//nim  : F1D0241081

const double EPSILON = 1e-10;
void tampilkanArray(double arr[], int ukuran) {
    for (int i = 0; i < ukuran; i++) {cout << fixed << setprecision(7) << setw(17) << arr[i];}
    cout << endl;
}

double perkalianTitik(double arr1[], double arr2[], int mulai, int akhir) {
    double hasil = 0;
    for (int i = mulai; i < akhir; i++) {hasil += arr1[i] * arr2[i];}
    return hasil;
}

double* eliminasiGauss(double A[][3], double B[], int n) {
    for (int p = 0; p < n; p++) {
        int barisMaks = p;
        for (int i = p + 1; i < n; i++) {
            if (abs(A[i][p]) > abs(A[barisMaks][p])) {barisMaks = i;}
        }swap(A[p], A[barisMaks]);     swap (B[p], B[barisMaks]);

        if (abs(A[p][p]) <= EPSILON) {throw runtime_error("Matriks singular atau hampir singular");}

        for (int i = p + 1; i < n; i++) {
            double alpha = A[i][p] / A[p][p];
            B[i] -= alpha * B[p];
            for (int j = p; j < n; j++) {A[i][j] -= alpha * A[p][j];}
        }
    }double* x = new double[n];
    for (int i = n - 1; i >= 0; i--) {x[i] = (B[i] - perkalianTitik(A[i], x, i + 1, n)) / A[i][i];}
    return x;
}

void hitungMatriksKoefisien(double data[][2], int derajat, double koefisien[][3], int n) {
    for (int i = 0; i < derajat; i++) {
        for (int j = 0; j < derajat; j++) {
            double jumlah = 0;
            for (int k = 0; k < n; k++) {jumlah += pow(data[k][0], i + j);}
            koefisien[i][j] = jumlah;
        }
    }koefisien[0][0] = n;
}

void hitungKonstanta(double data[][2], int derajat, double koefisien[][3], double konstanta[], int n) {
    for (int i = 0; i < derajat; i++) {
        double jumlah = 0;
        for (int j = 0; j < n; j++) {jumlah += pow(data[j][0], i) * data[j][1];}
        konstanta[i] = jumlah;
    }
}

double count(double X[], double Y[], double z, int order) {
    double result = 0.0;
    for (int i = 0; i <= order; i++) {
        double pi = 1.0;
        for (int j = 0; j <= order; j++) {if (i != j) {pi *= (z - X[j]) / (X[i] - X[j]);}}result += Y[i] * pi;
    }return result;
}

void tampilkanTabelLagrange(double X[], double Y[], int n, double z, double hasilLagrange) {
    cout << "+------------+--------------------+--------------------+" << endl;
    cout << "|    X[i]   |        Y[i]         |  Nilai Lagrange    |" << endl;
    cout << "+------------+--------------------+--------------------+" << endl;
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(10) << X[i] << " | " << setw(18) << Y[i] << " | " << setw(18) << hasilLagrange << " |" << endl;
    }
    cout << "+------------+--------------------+--------------------+" << endl;
    cout << "Nilai Lagrange untuk z = " << z << " : " << hasilLagrange << endl;
}

int main() {
    double data[][2] = {{1, 1.5577}, {2, 1.2131}, {3, 0.9447}, {4, 0.7358},
                        {5, 0.5730}, {6, 0.4462}, {7, 0.3476}, {8, 0.2706}};
    int n = sizeof(data) / sizeof(data[0]);
    double* hasil, error = 0;

    int derajat = 2;
    double matriksKoefisien[derajat][3];
    hitungMatriksKoefisien(data, derajat, matriksKoefisien, n);
    double konstanta[derajat];
    hitungKonstanta(data, derajat, matriksKoefisien, konstanta, n);
    cout << "\nSolusi regresi linier a + bx:" << endl;
    tampilkanArray(konstanta, derajat);
    hasil = eliminasiGauss(matriksKoefisien, konstanta, derajat);
    cout << "Persamaan: (" << hasil[1] << ") + (" << hasil[0] << ")x" << endl;

    for (int i = 0; i < n; i++) {error += pow((hasil[1] + hasil[0] * data[i][0] - data[i][1]), 2);}
    error = sqrt(error / n);
    cout << "Nilai error: " << error << endl;

    derajat = 3;
    hitungMatriksKoefisien(data, derajat, matriksKoefisien, n);
    hitungKonstanta(data, derajat, matriksKoefisien, konstanta, n);
    cout << "\nSolusi regresi kuadrat ax^2 + bx + c:" << endl;
    tampilkanArray(konstanta, derajat);
    hasil = eliminasiGauss(matriksKoefisien, konstanta, derajat);
    cout << "Persamaan: (" << hasil[2] << ")x^2 + (" << hasil[1] << ")x + (" << hasil[0] << ")" << endl;

    error = 0;
    for (int i = 0; i < n; i++) {error += pow((hasil[2] * pow(data[i][0], 2) + hasil[1] * data[i][0] + hasil[0] - data[i][1]), 2);}
    error = sqrt(error / n);
    cout << "Nilai error: " << error << endl;
    derajat = 2;
    double dataLog[n][2];
    for (int i = 0; i < n; i++) {
        dataLog[i][0] = data[i][0];
        dataLog[i][1] = log(data[i][1]);
    }
    hitungMatriksKoefisien(dataLog, derajat, matriksKoefisien, n);
    hitungKonstanta(dataLog, derajat, matriksKoefisien, konstanta, n);

    cout << "\nSolusi regresi eksponensial ae^bx:" << endl;
    tampilkanArray(konstanta, derajat);
    hasil = eliminasiGauss(matriksKoefisien, konstanta, derajat);
    cout << "Persamaan: (" << exp(hasil[0]) << ")e^(" << hasil[1] << "x)" << endl;


    double X[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    double Y[] = {1.5577, 1.2131, 0.9447, 0.7358, 0.5730, 0.4462, 0.3476, 0.2706};
    double z = 5.5;

    cout << "\nMetode Lagrange Interpolation:" << endl;
    double lagrangeResult = count(X, Y, z, sizeof(X) / sizeof(X[0]) - 1);
    tampilkanTabelLagrange(X, Y, sizeof(X) / sizeof(X[0]), z, lagrangeResult);
    delete[] hasil;
    return 0;
}
