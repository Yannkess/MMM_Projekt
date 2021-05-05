#include "obliczenia.h"
#include <cmath>
#include <conio.h>






Obliczenia::Obliczenia()
{
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
