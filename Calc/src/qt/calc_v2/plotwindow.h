#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>

#include "../../controller.h"

namespace Ui {
class PlotWindow;
}

namespace s21 {
class PlotWindow : public QDialog {
  Q_OBJECT

 public:
  PlotWindow() {}
  explicit PlotWindow(QWidget *parent, Controller const &controller);
  ~PlotWindow();
  void plotting();

 private:
  Ui::PlotWindow *ui;
  Controller controller_;

 signals:
  void plotSignal(double, double, double, double);

 private slots:
  void on_replot_clicked();
};
}  // namespace s21
#endif  // PLOTWINDOW_H
