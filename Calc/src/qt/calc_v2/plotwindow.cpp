#include "plotwindow.h"

#include "ui_plotwindow.h"

namespace s21 {
PlotWindow::PlotWindow(QWidget *parent, Controller const &controller)
    : QDialog(parent), ui(new Ui::PlotWindow), controller_(controller) {
  ui->setupUi(this);
}

PlotWindow::~PlotWindow() { delete ui; }

void PlotWindow::plotting() {
  ui->widget->clearGraphs();
  double X = ui->min_X->value();
  double dx = ui->dx->value();
  QVector<double> x, y;
  while (X < ui->max_X->value()) {
    x.push_back(X);
    double Y = controller_.getResult(X);
    y.push_back(Y);
    X += dx;
  }
  ui->widget->xAxis->setRange(ui->min_X->value(), ui->max_X->value());
  ui->widget->yAxis->setRange(ui->min_Y->value(), ui->max_Y->value());
  ui->widget->addGraph();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui->widget->graph()->setData(x, y);
  ui->widget->replot();
}

void PlotWindow::on_replot_clicked() { plotting(); }
}  // namespace s21
