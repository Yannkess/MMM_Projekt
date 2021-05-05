#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QString>
#include <QButtonGroup>
#include <QDebug>




#include "obliczenia.h"
#include "wykres.h"


#define startPoint 10;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int a_2 = startPoint
    int a_1 = startPoint
    int a_0 = startPoint
    int Amp = startPoint
    int T   = 0;
    int Tin = 10;
    int b_1 = 6;
    int b_0 = 5;

    QString textTransmitation;
    void createTextTransmitation();
    void display_remarks();

private slots:

    void on_lineEdit_A2_textChanged();

    void on_lineEdit_A1_textChanged(const QString &arg1);

    void on_lineEdit_A0_textChanged(const QString &arg1);

    void on_lineEdit_Amp_textChanged(const QString &arg1);

    void on_lineEdit_Tin_textChanged(const QString &arg1);

    void on_lineEdit_Opoz_textChanged(const QString &arg1);

    void on_p_sinus_clicked();

private:

    Ui::MainWindow *ui;
    Obliczenia obliczenia;
    Wykres *wykres;
    Wykres *drugiwykres;
};
#endif // MAINWINDOW_H
