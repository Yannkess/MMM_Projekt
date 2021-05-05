#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createTextTransmitation();
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

    textTransmitation.append("\n" + QString::number(b_1) + "s + " + QString::number(b_0) +"\n");
    textTransmitation.append("-------------------   * exp ( -s * "+QString::number(T));
    textTransmitation.append(QString::number(a_2));
    textTransmitation.append(")\n + s^2 + " + QString::number(a_1) + "s + ");
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
    if(T==0)
    {
        mistake += " Opóźnienie";
    }
    if(Amp==0)
    {
        mistake += " Amplituda";
    }
    ui->textBrowser->setText(mistake);

    if(a_0 != 0 && a_1 != 0 && a_2 != 0 && Tin != 0 && T!=0 && Amp !=0)


        ui->textBrowser->setText(" ");

}



void MainWindow::on_textEdit_A2_textChanged()
{
    QString a_2_string = ui->lineEdit_A2->text();
    bool convertOK;
    a_2 = a_2_string.toInt(&convertOK);
    display_remarks();
    createTextTransmitation();
}
