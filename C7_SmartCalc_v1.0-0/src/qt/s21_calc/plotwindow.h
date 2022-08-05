#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>


extern "C" {
#include "../../parser.h"
}

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

private:
    Ui::PlotWindow *ui;

public slots:
void plot_slot(char *, double, double, double, double);
};



#endif // PLOTWINDOW_H
