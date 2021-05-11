#ifndef WYKRES_H
#define WYKRES_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QtCharts>
#include <QChartView>
#include <QAbstractAxis>
#include <QValueAxis>
#include <QLogValueAxis>

enum type_of_chart {WEJSCIE, WYJSCIE, AMPLITUDOWY, FAZOWY};
enum input_signal {SQUARE, HEAVYSIDE, SINUS};

class Wykres : public QChart
{

public:
    Wykres(type_of_chart typ_wykresu);

    void setData(type_of_chart typ_wykresu, QLineSeries *danePrzekazane);

    void ustawPrzedzialyWykresu(type_of_chart typ_wykresu , double bottomX, double topX, double bottomY, double topY);


    type_of_chart typeOfChart;
    QLineSeries *daneNaWykresie;

    QValueAxis *axisX;
    QValueAxis *axisY;
    QLogValueAxis *laxisX;
    QLogValueAxis *laxisY;

   private:
    void linLinAxis();
    void loglogAxis();
    void loglinAxis();
};

#endif // WYKRES_H
