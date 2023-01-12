#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_diff, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_open_brecket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(digits_numbers()));
}

View::~View() { delete ui; }

void View::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  controller_.putStringElement(button->text().toStdString());
  ui->out_string->setText(QString::fromStdString(controller_.getExpr()));
}

void View::on_pushButton_ac_clicked() {
  controller_.clearExrp();
  controller_.clearModel();
  ui->out_string->setText("");
  ui->out_result->setText("0");
}

void View::on_pushButton_delete_clicked() {
  controller_.deleteSymbol();
  ui->out_string->setText(QString::fromStdString(controller_.getExpr()));
}

void View::on_pushButton_result_clicked() {
  try {
    ui->statusBar->clearMessage();
    if (ui->plot->checkState() == false) {
      controller_.setPlotState(false);
      double x = ui->input_X->value();
      ui->out_result->setText(
          QString::number(controller_.getResult(x), 'g', 10));
    } else {
      controller_.setPlotState(true);
      plotWindow = new PlotWindow(this, controller_);
      plotWindow->plotting();
      plotWindow->show();
    }
  } catch (std::runtime_error &e) {
    ui->statusBar->showMessage(e.what(), 0);
    controller_.clearModel();
  }
}

void View::on_pushButton_calculate_clicked() {
  QStringList labels = QObject::tr(
                           "Сумма платежа;Платеж по основному долгу;Платеж "
                           "по процентам;Остаток долга")
                           .simplified()
                           .split(";");

  creditController_ = new CreditController(
      ui->doubleSpinBox_credit_sum->value(), ui->spinBox_term->value(),
      ui->doubleSpinBox_bid->value(), ui->radioButton_annuity->isChecked());

  ui->radioButton_annuity->isEnabled();

  ui->lineEdit_overpayment->setText(
      QString::number(creditController_->getSumOverPayment(), 'f', 2));
  ui->lineEdit_total->setText(
      QString::number(creditController_->getTotal(), 'f', 2));
  QStandardItemModel *model = creditController_->getCreditModel();
  model->setHorizontalHeaderLabels(labels);
  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}
}  // namespace s21
