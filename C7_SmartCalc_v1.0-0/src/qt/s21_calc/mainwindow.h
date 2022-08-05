#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtMath>
#include <QStandardItemModel>
#include "plotwindow.h"

extern "C" {
#include "../../parser.h"
}



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
 //   void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void digits_numbers();
    void on_pushButton_dot_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_result_clicked();

//    void on_plot_stateChanged(int arg1);

    void on_pushButton_calculate_clicked();

signals:
    void plot_signal(char *, double, double, double, double);

private:
    Ui::MainWindow *ui;
    PlotWindow *window;
    QString str;
};


#endif // MAINWINDOW_H
