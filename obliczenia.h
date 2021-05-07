#ifndef OBLICZENIA_H
#define OBLICZENIA_H

#include <QtCharts>
#include <QLineSeries>
#include <cmath>
#include <QDebug>
#include <complex>



#define h 0.01 // krok obliczeń
#define T 100 // całkowity czas symulacji – przedział [0 , T]
#define L 25 // liczba okresów sygnału sinus w przedziale T
#define N = 3

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


    void metoda_taylora_sinus();
    void Obliczenia::metoda_eulera_fala_prostokatna();
    void Obliczenia::metoda_eulera_skok_jednostkowy();




    // pomocniczy typ – kolejne bajty danej ’double’
    typedef union { char c[sizeof(double)]; double d; } Box;
    // zmienne globalne w programie
    double u[(int)(1.0 * T / h) + 1]; // sygnał wejściowy
    double u1p[(int)(1.0 * T / h) + 1]; // pierwsza pochodna sygnału wejściowego

    // Euler
    double us[(int)(1.0*T/h)+1]; // sygnał wejściowy sinus
    double uf[(int)(1.0*T/h)+1]; // sygnał wejściowy fala prostokątna


    double y[(int)(1.0 * T / h) + 1]; // sygnał wyjściowy
    double y1p[(int)(1.0 * T / h) + 1]; // pierwsza pochodna sygnału wyjściowego
    double y2p[(int)(1.0 * T / h) + 1]; // druga pochodna sygnału wyjściowego
    double y3p[(int)(1.0 * T / h) + 1]; // trzecia pochodna sygnału wyjściowego







    //---------------------
    // Do macierzy

    void wypelnienie_macierzy();





};

#endif // OBLICZENIA_H
