#ifndef OBLICZENIA_H
#define OBLICZENIA_H

#include <QtCharts>
#include <QLineSeries>
#include <cmath>
#include <QDebug>
#include <complex>


#define h 0.001 // krok obliczeń
#define T 10 // całkowity czas symulacji – przedział [0 , T]
#define L 2.5 // liczba okresów sygnału sinus w przedziale T

#define PI 3.14159265 // liczba PI



class Obliczenia
{
public:
    Obliczenia();


    double checkMaksimum();
    double checkMinimum();


    double a_0=10;
    double a_1=10;
    double a_2=10;
    double b_1=10;
    double b_0=10;
    int total =  0;
    double M = 8; // ampliuda sygnału


    void sinus();

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



};

#endif // OBLICZENIA_H
