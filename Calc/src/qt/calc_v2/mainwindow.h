#ifndef VIEW_H
#define VIEW_H

#include <plotwindow.h>

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include <QtMath>

#include "../../controller.h"
#include "creditcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 private:
  Ui::View *ui;
  PlotWindow *plotWindow;
  Controller controller_;
  CreditController *creditController_ = nullptr;

 public:
  View(QWidget *parent = nullptr);
  ~View();

  Controller getController() { return controller_; }

 private slots:
  void digits_numbers();
  void on_pushButton_ac_clicked();
  void on_pushButton_delete_clicked();
  void on_pushButton_result_clicked();
  void on_pushButton_calculate_clicked();
};
}  // namespace s21

#endif  // VIEW_H
