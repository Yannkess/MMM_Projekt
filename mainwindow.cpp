#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createTextTransmitation();
    this->setWindowTitle("Projekt - Marcin Jankowski, Kacper Wierciński");
    ui->plainTextEdit->setReadOnly(true);

    wykres = new Wykres(WEJSCIE);
    ui->graphicsView->setChart(wykres);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createTextTransmitation()
{
    ui->plainTextEdit->clear();
    textTransmitation.clear();


    textTransmitation.append("Postać transmitancji H(s)" );
    textTransmitation.append("\n                " + QString::number(b_1) + "s + " + QString::number(b_0) +"\n");
    textTransmitation.append("-------------------------------   * exp ( -s * "+QString::number(opoz));
    textTransmitation.append(")\n s^3 + " + QString::number(a_2) + "s^2 + " + QString::number(a_1) + "s + ");
    textTransmitation.append(QString::number(a_0));

    ui->plainTextEdit->setPlainText(textTransmitation);
}



void MainWindow::display_remarks()
{
    QString mistake = "bledne wspolczynniki:";
    if(a_0 == 0)
    {
        mistake += " a0";
    }
    if(a_1 == 0)
    {
        mistake += " a1";
    }
    if(a_2 == 0)
    {
        mistake += " a2";
    }


    ui->textBrowser->setText(mistake);

    if(a_0 != 0 && a_1 != 0 && a_2 != 0)
        ui->textBrowser->setText(" ");
}

void MainWindow::on_lineEdit_A2_textChanged()
{
    QString a_2_string = ui->lineEdit_A2->text();

    bool convertOK;
    a_2 = a_2_string.toInt(&convertOK);

    display_remarks();
    createTextTransmitation();
    obliczenia.a_2 = this->a_2;
}

void MainWindow::on_lineEdit_A1_textChanged()
{
    QString a_1_string = ui->lineEdit_A1->text();

    bool convertOK;
    a_1 = a_1_string.toInt(&convertOK);

    display_remarks();
    createTextTransmitation();
    obliczenia.a_1 = this->a_1;
}

void MainWindow::on_lineEdit_A0_textChanged()
{
    QString a_0_string = ui->lineEdit_A0->text();

    bool convertOK;
    a_0 = a_0_string.toInt(&convertOK);

    display_remarks();
    createTextTransmitation();
    obliczenia.a_0 = this->a_0;
}

void MainWindow::on_lineEdit_B1_textChanged()
{
    QString B1_string = ui->lineEdit_B1->text();

    bool convertOK;
    b_1 = B1_string.toInt(&convertOK);

    display_remarks();
    createTextTransmitation();
    obliczenia.b_1 = this->b_1;
}

void MainWindow::on_lineEdit_B0_textChanged()
{
    QString B0_string = ui->lineEdit_B0->text();

    bool convertOK;
    b_0 = B0_string.toInt(&convertOK);

    display_remarks();
    createTextTransmitation();
    obliczenia.b_0 = this->b_0;
}

void MainWindow::on_lineEdit_Opoz_textChanged()
{
    QString Opoz_string = ui->lineEdit_Opoz->text();

    bool convertOK;
    opoz = Opoz_string.toInt(&convertOK);

    display_remarks();
    createTextTransmitation();
}

void MainWindow::on_p_skok_jedn_clicked()
{
    sinus = false;
    jednostkowy = true;
    prostokat = false;

    QLineSeries *dane = new QLineSeries();
    obliczenia.metoda_eulera_skok_jednostkowy();

    for (int i = 0; i < obliczenia.total; i++)
    {
         double czas = i * h;

        dane->append(czas, obliczenia.Ujednostkowy[i]);
    }

    wykres->setData(WEJSCIE,dane);
    wykres->ustawPrzedzialyWykresu(WEJSCIE,0,T,-obliczenia.M, obliczenia.M);
}

void MainWindow::on_p_fala_prost_clicked()
{
    sinus = false;
    jednostkowy = false;
    prostokat = true;

    QLineSeries *dane = new QLineSeries();
    obliczenia.metoda_eulera_fala_prostokatna();

    for (int i = 0; i < obliczenia.total; i++)
    {
        double czas = i * h;

        dane->append(czas, obliczenia.Ufala[i]);
    }

    wykres->setData(WEJSCIE,dane);
    wykres->ustawPrzedzialyWykresu(WEJSCIE,0,T,-obliczenia.M, obliczenia.M);
}

void MainWindow::on_p_sinus_clicked()
{
    sinus = true;
    jednostkowy = false;
    prostokat = false;

    QLineSeries *dane = new QLineSeries();
    obliczenia.metoda_taylora_sinus();

    for (int i = 0; i <obliczenia.total; i++)
    {
         double czas = i * h;

        dane->append(czas, obliczenia.u[i]);
    }

    wykres->setData(WEJSCIE,dane);
    wykres->ustawPrzedzialyWykresu(WEJSCIE,0,T,-obliczenia.M, obliczenia.M);
}


void MainWindow::on_p_syg_wyj_clicked()
{
    QLineSeries *dane = new QLineSeries();

    if(sinus)
        obliczenia.metoda_taylora_sinus();
    else if(prostokat)
       obliczenia.metoda_eulera_fala_prostokatna();
    else if(jednostkowy)
       obliczenia.metoda_eulera_skok_jednostkowy();

    drugiwykres = new Wykres(WYJSCIE);

    opoz = opoz * 1000;

    for (int i = 0; i < obliczenia.total-1 + opoz; i++)
    {
         double czas = i * h;
         if(i < opoz)
         dane->append(czas, 0);
         else
        dane->append(czas, obliczenia.y[i - opoz]);
    }

    drugiwykres->setData(WYJSCIE,dane);
    drugiwykres->ustawPrzedzialyWykresu(WYJSCIE,0,T,obliczenia.checkMinimum(), obliczenia.checkMaksimum());

    ui->graphicsView_2->setChart(drugiwykres);

    stabilnosc();
}

void MainWindow::on_p_char_amp_clicked()
{
    trzeciwykres = new Wykres(AMPLITUDOWY);
    QLineSeries *dane = new QLineSeries();

    obliczenia.widmo_amplitudowe();
    dane = obliczenia.obliczaneDane;

    trzeciwykres->setData(AMPLITUDOWY,dane);
    trzeciwykres->ustawPrzedzialyWykresu(AMPLITUDOWY,0.01,10000,obliczenia.minZakres, obliczenia.maxZakres);

    int zakres  = int(((abs(obliczenia.maxZakres) + abs(obliczenia.minZakres))) / 20);
    trzeciwykres->axisY->setTickCount(zakres + 1);

    ui->graphicsView_2->setChart(trzeciwykres);
}

void MainWindow::on_p_char_faz_clicked()
{
    trzeciwykres = new Wykres(FAZOWY);
    QLineSeries *dane = new QLineSeries();

    obliczenia.widmo_fazowe();
    dane = obliczenia.obliczaneDane;

    trzeciwykres->setData(FAZOWY,dane);
    trzeciwykres->ustawPrzedzialyWykresu(FAZOWY,0.01,10000,obliczenia.minZakres, obliczenia.maxZakres);

    int zakres  = int(((abs(obliczenia.maxZakres) + abs(obliczenia.minZakres))) / 40);
    trzeciwykres->axisY->setTickCount(zakres + 1);

    ui->graphicsView_2->setChart(trzeciwykres);
}

void MainWindow::stabilnosc()
{
    bool warunek = obliczenia.warunek_stabilnosci();
    if(warunek)
        ui->textBrowser_2->setText("Warunek stabilności spełniony.");
    else
        ui->textBrowser_2->setText("Warunek stabilności nie jest spełniony.");
}




