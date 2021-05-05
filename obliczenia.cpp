#include "obliczenia.h"
#include <cmath>
#include <conio.h>

#define h 0.001 // krok obliczeń
#define T 10.0 // całkowity czas symulacji – przedział [0 , T]
#define L 2.5 // liczba okresów sygnału sinus w przedziale T
#define M 8.0 // amplituda sygnału sinus
#define PI 3.14159265 // liczba PI
// pomocniczy typ – kolejne bajty danej ’double’
typedef union { char c[sizeof(double)]; double d; } Box;
// zmienne globalne w programie
double u[(int)(1.0 * T / h) + 1]; // sygnał wejściowy
double u1p[(int)(1.0 * T / h) + 1]; // pierwsza pochodna sygnału wejściowego


double y[(int)(1.0 * T / h) + 1]; // sygnał wyjściowy
double y1p[(int)(1.0 * T / h) + 1]; // pierwsza pochodna sygnału wyjściowego
double y2p[(int)(1.0 * T / h) + 1]; // druga pochodna sygnału wyjściowego
double y3p[(int)(1.0 * T / h) + 1]; // trzecia pochodna sygnału wyjściowego

Box z; // zmienna: pojedyncza wartość sygnału (u lub y)
// program główny



Obliczenia::Obliczenia()
{
    int i, j, total;
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

    for (i = 0; i < total; i++) {
        double k = u[i];

    }


    for (i = 0; i < total; i++) {
        double k = y[i];

    }



}
}
