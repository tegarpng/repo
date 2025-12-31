#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

//nama : Muhammad Tegar Bijanta
//nim  : F1D0241081

float fungsi (float x){
    return (pow(x,2)-(2*x)+1) - (pow(x,3)-((x+2)*(exp(-2*x)))+1);
}

float selisih(float a,float b){
    return(a+b)/2;
}

int main(){
    float a, b, fa, fb, toleransi;
    int N = 60; int pilih;
    cout << "Masukkan nilai a : ";cin >> a;
    cout << "Masukkan nilai b : ";cin >> b;
    cout << "Pilih nilai toleransi : \n1. 0.0001\n2. 0.000001\n3.0.000000000001\n4. Isi bebas\nPilih :"; cin >> pilih;
    if(pilih == 1){toleransi = 0.0001;
    }else if(pilih == 2){
        toleransi = 0.000001;
    }else if(pilih == 3){
        toleransi = 0.000000000001;
    }else if(pilih == 4){
        cout << "Masukkan nilai toleransi : ";cin >> toleransi;
    }else{
        cout << "Pilihan tidak valid" << endl;
    }
    cout << fixed << setprecision(6);
    cout << "Nilai toleransi = " << toleransi << endl;
    cout << "Nilai x awal = " << selisih(a, b) << endl;
    if (fungsi(a) * fungsi(b) > 0){
        cout << "Interval tidak valid, f(a) dan f(b) punya tanda sama" <<endl;
        return 0;
    }
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(10) << "Iterasi" << setw(15) << "a" << setw(15)<< "b" << setw(15) << "x" << setw(20) << "f(x)" << setw(20) << "f(a)"<<
    setw(20) << "abs(b-a)" << " |" <<setw(10) << "Ket" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    int i = 0;
    float x, error;
    fa = fungsi(a);
    fb = fungsi(b);
    while(i <= N){
        x = selisih(a, b);error = abs(b-a);
        bool ket = (error > toleransi) ? true : false;
        cout << setw(8) << i << setw(20) << a << setw(15) << b << setw(15) << x << setw(15) 
        << fungsi(x) << setw(22) << fa << setw(22) << error<< setw(10) << (ket ? "lanjut" : "stop") << endl;
        if(fungsi(a)*fungsi(x) < 0){
            b = x;
            fb = fungsi(x);
        }else {
            a = x;
        fa = fungsi(x);
        }

        if(error <= toleransi){break;}
        i++;
    }
    cout << "Nilai x = " << x << ", nilai error = " << error << endl;
    return 0;
}