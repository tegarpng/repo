#include <iostream>
#include <iomanip>
using namespace std;

//nama : Muhammad Tegar Bijanta
//nim  : F1D0241081

const int N = 10;
// Fungsi menukar baris
void tukarBaris(double A[N][N], double b[N], int baris1, int baris2) {
    for (int i = 0; i < N; i++) {
        double temp = A[baris1][i];
        A[baris1][i] = A[baris2][i];
        A[baris2][i] = temp;
    }
    double tempB = b[baris1];
    b[baris1] = b[baris2]; b[baris2] = tempB;
}
// Fungsi menukar kolom
void tukarKolom(double A[N][N], int kolom1, int kolom2, int urutanKolom[N]) {
    for (int i = 0; i < N; i++) {
        double temp = A[i][kolom1];
        A[i][kolom1] = A[i][kolom2];
        A[i][kolom2] = temp;
    }
    int tempK = urutanKolom[kolom1];
    urutanKolom[kolom1] = urutanKolom[kolom2];
    urutanKolom[kolom2] = tempK;
}
// Fungsi eliminasi Gauss
void eliminasiGauss(double A[N][N], double b[N], double x[N]) {
    int urutanKolom[N];
    for (int i = 0; i < N; i++) urutanKolom[i] = i;
    // Eliminasi maju
    for (int i = 0; i < N; i++) {
        // Jika elemen diagonal nol → tukar baris
        if (A[i][i] == 0) {
            bool swapped = false;
            for (int j = i + 1; j < N; j++) {
                if (A[j][i] != 0) {
                    tukarBaris(A, b, i, j);
                    swapped = true;
                    break;
                }
            }
            // Jika masih nol → tukar kolom
            if (!swapped) {
                for (int k = i + 1; k < N; k++) {
                    if (A[i][k] != 0) {
                        tukarKolom(A, i, k, urutanKolom);
                        swapped = true;
                        break;
                    }
                }
            }
            if (!swapped) {
            cout << "Sistem tidak dapat diselesaikan (elemen diagonal nol dan tidak bisa ditukar)." << endl;
            return;
            }
        }
        // Eliminasi baris di bawahnya
        for (int j = i + 1; j < N; j++) {
            double faktor = A[j][i] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= faktor * A[i][k];
            }
            b[j] -= faktor * b[i];
        } 
    }
    // Substitusi balik
    for (int i = N - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < N; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
    // Urutkan hasil sesuai kolom semula
    double temp[N];
    for (int i = 0; i < N; i++) temp[i] = x[i];
    for (int i = 0; i < N; i++) x[urutanKolom[i]] = temp[i];
}

int main() {
    const int n = N;
    double A[N][N] = {
        {0, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 4, 7, 3, 9, 2, 6, 5, 8, 10},
        {2, 6, 5, 8, 1, 4, 3, 9, 10, 7},
        {3, 9, 1, 6, 2, 10, 4, 7, 5, 8},
        {4, 7, 8, 2, 10, 9, 5, 6, 3, 1},
        {5, 3, 10, 9, 6, 8, 7, 1, 2, 4},
        {6, 1, 2, 10, 4, 5, 8, 3, 9, 7},
        {7, 10, 4, 5, 3, 1, 9, 2, 6, 8},
        {8, 5, 9, 1, 7, 3, 2, 4, 10, 6},
        {9, 8, 6, 7, 5, 2, 1, 10, 4, 3}
    };
    // v = 1
    double b[N] = {1, -1, 1, -1, 1, -1, 1, -1, 1, -1};
    double x[N];
    cout << "Matrix A:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << A[i][j];
        }
        cout << endl;
    }
    cout << "\nVektor b:\n";
    for (int i = 0; i < n; i++) cout << setw(5) << b[i];
    cout << endl;
    eliminasiGauss(A, b, x);
    cout << "\nHasil penyelesaian (x):\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) <<
        x[i] << endl;
    }
    return 0;
}