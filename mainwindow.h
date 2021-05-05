#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



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

    void on_textEdit_A2_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
