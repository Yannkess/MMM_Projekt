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
    int i;
    double  w;

    total = sizeof(u) / sizeof(u[0]);   // rozmiar wektorów danych
     w = 2.0 * PI * L / T;              // częstotliwość sinusoidy

    for(i = 0; i < total; i++)
        u[i] = M * sin(w * i * h);

    wypelnienie_macierzy();

    xi_1.n[0] = 0; xi_1.n[1] = 0; xi_1.n[2] = 0;

    for (i = 0; i < total; i++)
        {
            Ax = A * xi_1;
            Bu = B * u[i];
            Cx = C * xi_1;
            Du = D * u[i];
            xi = Ax + Bu; xi = xi * h;
            xi = xi_1 + xi; xi_1 = xi;
            y[i] = Cx + Du;
        }
}


void Obliczenia::fala_prostokatna()
{
    int i;
    double  w;

    total = sizeof(u) / sizeof(u[0]);   // rozmiar wektorów danych
     w = 2.0 * PI * L / T;              // częstotliwość sinusoidy

    for(i = 0; i < total; i++)          // sygnał wejściowy fala prostokątna obliczona na podstawie sygnału sinus
    {
        u[i] = M * sin(w * i * h);      // Sinus
        Ufala[i]=((u[i] > 0) ? M : -M); // Fala prostokątna
    }

    wypelnienie_macierzy();

    xi_1.n[0] = 0; xi_1.n[1] = 0; xi_1.n[2] = 0;

    for (i = 0; i < total; i++)
        {
            Ax = A * xi_1;
            Bu = B * Ufala[i];
            Cx = C * xi_1;
            Du = D * Ufala[i];
            xi = Ax + Bu; xi = xi * h;
            xi = xi_1 + xi; xi_1 = xi;
            y[i] = Cx + Du;
        }
}

void Obliczenia::skok_jednostkowy()
{
    int i;
    double  w;

    total = sizeof(u) / sizeof(u[0]);   // rozmiar wektorów danych
     w = 2.0 * PI * L / T;              // częstotliwość sinusoidy

    for(i = 0; i < total; i++)          // skok jednostkowy
        Ujednostkowy[i] = M;

    wypelnienie_macierzy();

    xi_1.n[0] = 0; xi_1.n[1] = 0; xi_1.n[2] = 0;

    for (i = 0; i < total; i++)
        {
            Ax = A * xi_1;
            Bu = B * Ujednostkowy[i];
            Cx = C * xi_1;
            Du = D * Ujednostkowy[i];
            xi = Ax + Bu;
            xi = xi * h;
            xi = xi_1 + xi;
            xi_1 = xi;
            y[i] = Cx + Du;
        }
}

void wyjscie(double t);


double Obliczenia::checkMaksimum()  // Sprawdzenie maksymalnej wartości funkcji wyjściowej
{
    double maksimumY = 0;
    for (int i = 0; i < total; i++)
    {
        if(y[i] > maksimumY)
        {
            maksimumY = y[i];
        }
    }

    return maksimumY;
}

double Obliczenia::checkMinimum()   // Sprawdzenie minimalnej wartości funkcji wyjściowej
{
    double minimum = 0;

    for (int i = 0; i < total; i++)
    {
        if(y[i] < minimum)
        {
            minimum = y[i];
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

//--------------

std::complex<double> Obliczenia::transmitancja_widmowa(double omega)
{
    std::complex<double> licznik;
    std::complex<double> mianownik;
    std::complex<double> j(0,1);

    licznik = b_1*j*omega + b_0;
    mianownik = j*j*j*omega*omega*omega + a_2*j*j*omega*omega + a_1*j*omega + a_0;

    return licznik / mianownik;
}

void Obliczenia::widmo_amplitudowe()
{
    maxZakres = -10000;
    minZakres = 10000;

    obliczaneDane = new QLineSeries();

    std::complex<double> yValue;
    double amplitude;

    for(double omega = 0.1; omega < 10000 ; omega *= 10)
    {
        for(double i = 1; i < 10; i++)
        {
            yValue = transmitancja_widmowa(omega * i);
            amplitude = 20 * log10(abs(yValue));
            obliczaneDane->append(omega * i, amplitude);
            zakres_widma(AMPLITUDA, amplitude);
        }
    }

}

void Obliczenia::widmo_fazowe()
{
    maxZakres = -10000;
    minZakres = 10000;
    obliczaneDane = new QLineSeries();
    std::complex<double> yValue;

    double argument;

    for(double omega = 0.1; omega < 10000; omega *= 10)
    {
        for(double i = 1; i < 10; i++)
        {
             yValue = transmitancja_widmowa(omega * i);
             argument = (arg(yValue) * 180) / PI;

             obliczaneDane->append(omega * i, argument);

             qDebug()<<"dla omega = "<< omega * i <<"argument = "<< argument;
             zakres_widma(FAZA,argument);
        }
    }
}

void Obliczenia::zakres_widma(int typ, double wartosc)
{
    if(wartosc < minZakres)
    {
        minZakres = wartosc;
    }

    if(wartosc > maxZakres)
    {
        maxZakres = wartosc;
        maxZakres = (floor((maxZakres / typ)) + 1) * typ;

        if(maxZakres <= 0)
        {
            switch(typ)
            {
            case AMPLITUDA:
                maxZakres = 20;
                break;
            case FAZA:
                minZakres = 45;
                break;
            }
        }
    }

    if (minZakres < 0)
        minZakres = (floor((minZakres/typ))) * typ;
    else
        minZakres = (floor((minZakres / typ)) + 1) * typ;
}

bool Obliczenia::warunek_stabilnosci()
{
    if((a_0 > 0) && (a_1 > 0) && (a_2 > 0))
    {
        if(((a_1 * a_2) - a_0) > 0)
             return true;
        else return false;
    }
    else return false;
}









