#include "obliczenia.h"
#include <cmath>
#include <conio.h>






Obliczenia::Obliczenia()
{

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
//Giga oro na macierzach

void Obliczenia::wypelnienie_macierzy()
{
    macierzA[0][0] = macierzA[0][2] = macierzA[1][0] = macierzA[1][1] = 0;
    macierzA[0][1] = macierzA[1][2] = 1;
    macierzA[2][0] = -1*a_0;
    macierzA[2][1] = -1*a_1;
    macierzA[2][2] = -1*a_2;

    for(int i = 0; i < 3; i++)          //Wypelnienie macierzy B
        for(int j = 0; j < 3; j++)
        {
            if(i == 2 && j == 0)       // Wstawienie 1 tylko w polu (2,0)
                macierzB[i][j] = 1;
            else
                macierzB[i][j] = 0;     //Reszta wypelniana zerami
        }

    for(int i = 0; i < 3; i++)          //Wypelnienie macierzy C
        for(int j = 0; j < 3; j++)
        {
            if(i == 0 && j == 0)       //Wstawienie b0 w polu (0,0)
                macierzC[i][j] = b_0;
            else if(i == 0 && j == 1)
                macierzC[i][j] = b_1;   //Wstawienie b1 w polu (0,1)
            else
                macierzC[i][j] = 0;     //Reszta wypelniona zerami
        }

    macierzD = 0;   //Jednoelementowa macierz D = 0




}
