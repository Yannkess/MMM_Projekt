#include "obliczenia.h"
#include <cmath>
#include <conio.h>


typedef struct { double n[3]; } Vect;
typedef struct { double n[3][3]; } Matr;
static Matr A;
static Vect B, C, Ax, Bu, xi, xi_1;
static double D, Cx, Du;


Obliczenia::Obliczenia()
{

}

 Vect operator+(const Vect& U, const Vect& V)
{
    Vect W;
    int i;
    for (i = 0; i < 3; i++)
        W.n[i] = U.n[i] + V.n[i];
    return W;
}
// mnożenie: wektor razy skalar - operator przeciążony
Vect operator*(const Vect& U, const double& d)
{
    Vect W;
    int i;
    for (i = 0; i < 3; i++)
        W.n[i] = U.n[i] * d;
    return W;
}
// mnożenie: macierz razy wektor - operator przeciążony
Vect operator*(const Matr& A, const Vect& V)
{
    Vect W;
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0, W.n[i] = 0; j < 3; j++)
            W.n[i] += A.n[i][j] * V.n[j];
    return W;
}
// mnożenie skalarne: wektor razy wektor - operator przeciążony
double operator*(const Vect& U, const Vect& V)
{
    int i;
    double s;
    for (i = 0, s = 0; i < 3; i++)
        s += U.n[i] * V.n[i];
    return s;
}

void Obliczenia::sinus(){
    int i, j;
    double  w;


    total = sizeof(u) / sizeof(u[0]); // rozmiar wektorów danych
    w = 2.0 * PI * L / T; // częstotliwość sinusoidy
    for (i = 0; i < total; i++) // sygnał wejściowy i jego pochodne
    {
        u[i] = M * sin(w * i * h); // sygnał wejściowy: u=M*sin(w*t) , t=i*h
        u1p[i] = M * w * cos(w * i * h); // pochodna 1: u’(t)

    }
    y[0] = 0; y1p[0] = 0; y2p[0] = 0; y3p

        [0] = 0; // zerowe warunki początkowe
    for (i = 0; i < total - 1; i++) // główna pętla obliczeń
    {
        y3p[i] = -a_2 * y2p[i] - a_1 * y1p[i] - a_0 * y[i] + b_1 * u1p[i] + b_0 * u[i];
        y2p[i + 1] = y2p[i] + h * y3p[i];
        y1p[i + 1] = y1p[i] + h * y2p[i] + (h * h / 2.0) * y3p[i] + (h * h * h / 6.0);
        y[i + 1] = y[i] + h * y1p[i] + (h * h / 2.0) * y2p[i] + (h * h * h / 6.0) * y3p[i];
    }
}


void Obliczenia::metoda_eulera_fala_prostokatna()
{

    int i, j;
    double  w;

    total = sizeof(u) / sizeof(u[0]); // rozmiar wektorów danych
     w = 2.0 * PI * L / T; // częstotliwość sinusoidy

    for( i=0; i<total; i++) // obliczenie pobudzenia – sinus lub fala prostokątna
     {
     us[i]=M*sin(w*i*h); // sygnał wejściowy sinus: u=M*sin(w*t) , t=i*h
     uf[i]=((us[i]>0)? M: -M); // sygnał wejściowy fala prostokątna
     }
    wypelnienie_macierzy();
    xi_1.n[0] = 0; xi_1.n[1] = 0; xi_1.n[2] = 0;

    for (i = 0; i < total; i++)
        {
            Ax = A * xi_1; Bu = B * uf[i]; Cx = C * xi_1; Du = D * uf[i];
            xi = Ax + Bu; xi = xi * h; xi = xi_1 + xi; xi_1 = xi; y[i] = Cx + Du;
        }

}

void Obliczenia::metoda_eulera_skok_jednostkowy()
{
    int i, j;
    double  w;

    total = sizeof(u) / sizeof(u[0]); // rozmiar wektorów danych
     w = 2.0 * PI * L / T; // częstotliwość sinusoidy

    for( i=0; i<total; i++) // obliczenie pobudzenia – sinus lub fala prostokątna
     {
     us[i]=M*sin(w*i*h); // sygnał wejściowy sinus: u=M*sin(w*t) , t=i*h
     uf[i] = ((us[i]>=-M)?M: - M); // skok jednostkowy
     }
    wypelnienie_macierzy();
    xi_1.n[0] = 0; xi_1.n[1] = 0; xi_1.n[2] = 0;

    for (i = 0; i < total; i++)
        {
            Ax = A * xi_1; Bu = B * uf[i]; Cx = C * xi_1; Du = D * uf[i];
            xi = Ax + Bu; xi = xi * h; xi = xi_1 + xi; xi_1 = xi; y[i] = Cx + Du;
        }
}

void wyjscie(double t);


double Obliczenia::checkMaksimum()
{
    double maksimumY=0;
    for (int i=0; i<total; i++)
    {
        if(y[i]>maksimumY)
        {
            maksimumY=y[i];
        }
    }
    return maksimumY;

}

double Obliczenia::checkMinimum()
{
    double minimum=0;
    for (int i=0; i<total; i++)
    {
        if(y[i]<minimum)
        {
            minimum=y[i];
        }
    }
    return minimum;
}

//------------------

void Obliczenia::wypelnienie_macierzy()
{
    A.n[0][0] = A.n[0][2] = A.n[1][0] = A.n[1][1] = 0;
    A.n[0][1] = A.n[1][2] = 1;
    A.n[2][0] = -1*a_0;
    A.n[2][1] = -1*a_1;
    A.n[2][2] = -1*a_2;

    B.n[0] = 0; B.n[1] = 0; B.n[2] = 1;
    C.n[0] = b_0; C.n[1] = b_1; C.n[2] = 0;
    D = 0;

}









