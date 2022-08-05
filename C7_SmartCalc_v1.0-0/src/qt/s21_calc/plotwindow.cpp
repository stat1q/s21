
extern "C" {
#include "../../parser.h"
}

#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::PlotWindow) {
  ui->setupUi(this);
}

PlotWindow::~PlotWindow() { delete ui; }

void PlotWindow::plot_slot(char *input_str, double minX, double maxX,
                           double minY, double maxY) {
 //int flag_err = 0;
 double X = minX;
 double dx = 0.05;

 QVector<double> x, y;

 while (X < maxX) {
  x.push_back(X);
  double Y = get_result(input_str, X);
//  double Y = expression_calc(result_stack, X, &flag_err);
  y.push_back(Y);
  X += dx;

//  if (flag_err == ERROR) {
//    Y = NAN;
//    // todo &????
//  }
 }

 ui->lineEdit->setText(input_str);
 ui->plot_widget->xAxis->setRange(minX, maxX);
 ui->plot_widget->yAxis->setRange(minY, maxY);
 ui->plot_widget->addGraph();
 ui->plot_widget->graph(0)->setLineStyle(QCPGraph::lsNone);
 ui->plot_widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
 ui->plot_widget->graph()->setData(x, y);
 }
  // printf("\nres = %lf", result);
 // free_stack(&result_stack);
  //return result;

  //ui->lineEdit->setText(str);





