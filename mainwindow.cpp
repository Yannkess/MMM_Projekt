#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createTextTransmitation();
    this->setWindowTitle("Metody Modelowania Matematycznego - Projekt - Marcin Jankowski, Kacper Wierciński");
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

    QString mistake="bledne wspolczynniki:";
    if(a_0==0)
    {
        mistake += " a0";
    }
    if(a_1==0)
    {
        mistake += " a1";
    }
    if(a_2==0)
    {
        mistake += " a2";
    }
    if(Tin==0)
    {
        mistake += " Okres wejścia";
    }
    if(Amp==0)
    {
        mistake += " Amplituda";
    }
    ui->textBrowser->setText(mistake);

    if(a_0 != 0 && a_1 != 0 && a_2 != 0 && Tin != 0 && Amp !=0)


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

void MainWindow::on_lineEdit_A1_textChanged(const QString &arg1)
{
    QString a_1_string = ui->lineEdit_A1->text();
    bool convertOK;
    a_1 = a_1_string.toInt(&convertOK);
    display_remarks();
    createTextTransmitation();
    obliczenia.a_1 = this->a_1;
}

void MainWindow::on_lineEdit_A0_textChanged(const QString &arg1)
{
    QString a_0_string = ui->lineEdit_A0->text();
    bool convertOK;
    a_0 = a_0_string.toInt(&convertOK);
    display_remarks();
    createTextTransmitation();
    obliczenia.a_0 = this->a_0;
}

void MainWindow::on_lineEdit_Amp_textChanged(const QString &arg1)
{
    QString Amp_string = ui->lineEdit_Amp->text();
    bool convertOK;
    Amp = Amp_string.toInt(&convertOK);
    display_remarks();
    createTextTransmitation();
    obliczenia.M = this->Amp;
}

void MainWindow::on_lineEdit_Tin_textChanged(const QString &arg1)
{
    QString Tin_string = ui->lineEdit_Tin->text();
    bool convertOK;
    Tin = Tin_string.toInt(&convertOK);
    display_remarks();
    createTextTransmitation();
}

void MainWindow::on_lineEdit_Opoz_textChanged(const QString &arg1)
{
    QString Opoz_string = ui->lineEdit_Opoz->text();
    bool convertOK;
    opoz = Opoz_string.toInt(&convertOK);
    display_remarks();
    createTextTransmitation();
}
void MainWindow::on_p_fala_prost_clicked()
{
    sinus = false;
    heavyside = false;
    prostokat = true;

    QLineSeries *dane =new QLineSeries();
    obliczenia.metoda_eulera_fala_prostokatna();

    for (int i=0; i<obliczenia.total; i++)
    {
         double czas = i*h;

        dane->append(czas, obliczenia.uf[i]);
    }

    wykres->setData(WEJSCIE,dane);
    wykres->ustawPrzedzialyWykresu(WEJSCIE,0,T/10,-obliczenia.M, obliczenia.M);
}

void MainWindow::on_p_sinus_clicked()
{
    sinus = true;
    heavyside = false;
    prostokat = false;

    QLineSeries *dane =new QLineSeries();
    obliczenia.sinus();

    for (int i=0; i<obliczenia.total; i++)
    {
         double czas = i*h;

        dane->append(czas, obliczenia.u[i]);
    }

    wykres->setData(WEJSCIE,dane);
    wykres->ustawPrzedzialyWykresu(WEJSCIE,0,T/10,-obliczenia.M, obliczenia.M);

}


void MainWindow::on_p_syg_wyj_clicked()
{
    QLineSeries *dane =new QLineSeries();

    obliczenia.metoda_eulera_fala_prostokatna();

    drugiwykres = new Wykres(WYJSCIE);

    opoz = opoz * 100;




    for (int i=0; i<obliczenia.total-1 + opoz; i++)
    {
         double czas = i*h;
         if(i<opoz)
         dane->append(czas, 0);
         else
        dane->append(czas, obliczenia.y[i - opoz]);
    }

    drugiwykres->setData(WYJSCIE,dane);
    drugiwykres->ustawPrzedzialyWykresu(WYJSCIE,0,T/10,obliczenia.checkMinimum(), obliczenia.checkMaksimum());
    ui->graphicsView_2->setChart(drugiwykres);
}


