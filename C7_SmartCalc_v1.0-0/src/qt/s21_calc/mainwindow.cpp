#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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
  connect(ui->pushButton_degree, SIGNAL(clicked()), this, SLOT(digits_numbers()));
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
  connect(ui->pushButton_open_brecket, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    str = (ui->out_string->text() + button->text());
    ui->out_string->setText(str);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->out_string->text().contains('.')))
    ui->out_string->setText((ui->out_string->text() + "."));
}

void MainWindow::on_pushButton_ac_clicked()
{
     ui->out_string->setText("");
     ui->out_result->setText("0");
}


void MainWindow::on_pushButton_delete_clicked()
{
   str =  ui->out_string->text();
   if(str != '\0') {
     str.chop(1);
   }
  ui->out_string->setText(str);
}


void MainWindow::on_pushButton_result_clicked()
{
    QByteArray ba = ui->out_string->text().toLocal8Bit();
    char *str = ba.data();
    char input_str[256] = {0};
    double x = 0.0;

    int i;
    for (i = 0; i < 255 && *str; i++) {
      input_str[i] = *str;
      str++;
    }

     if(ui->plot->checkState() == false) {
         x = ui->input_X->value();
         double res = get_result(input_str, x);
         ui->out_result->setNum(res);
         qDebug() << "HELLO" << res;
         qDebug() << str;
     } else {
         // if nan!!!!
//       window.exec();
         window = new PlotWindow(this);
         connect(this, &MainWindow::plot_signal, window, &PlotWindow::plot_slot);
//         symb_st *input_stack = NULL;
//         int flag_err = parser(&input_stack, str);
//         symb_st *result_stack = get_polish(input_stack);

//         if (flag_err != 1) {
             emit plot_signal(input_str, ui->min_X->value(), ui->max_X->value(), ui->min_Y->value(), ui->max_Y->value());
               window->show();
//         }

//         on_plot_stateChanged(true);
     }
}


void add_table(double d, QStandardItemModel *model, int i, int j) {
  QStandardItem *item = new QStandardItem(QString::number(d, 'f', 2));
  model->setItem(i, j, item);
}

void MainWindow::on_pushButton_calculate_clicked()
{
    QStandardItemModel *model = new QStandardItemModel();
    QStringList labels = QObject::tr(
                             "Сумма платежа;Платеж по основному долгу;Платеж "
                             "по процентам;Остаток долга")
                             .simplified()
                             .split(";");
    model->setHorizontalHeaderLabels(labels);

    double amount = ui->doubleSpinBox_credit_sum->value();  // сумма кредита
    int term = ui->spinBox_term->value();               // срок кредита
  /*  double rate = ui->doubleSpinBox_bid->value();*/  // процентная ставка
    double sum_overpayment = 0.0;  // сумма переплаты
    double bid = (ui->doubleSpinBox_bid->value() / 12) / 100;  // процентная ставка в месяц
    double total = 0.0;        // общая сумма выплат
    double debt_balance = amount;  // остаток долга
    ui->radioButton_annuity->isEnabled();
    if (ui->radioButton_annuity->isChecked()) {
      double sum_payment =
          roundf(amount * (bid / (1 - pow(1 + bid, -term))) *
                 100) /
          100;
      sum_overpayment = sum_payment * term - amount;
      for (int i = 0; i < term; i++) {
        double overpayment = debt_balance * bid;
        double payment = roundf((sum_payment - overpayment) * 100) / 100;
        debt_balance -= payment;
        add_table(sum_payment, model, i, 0);
        add_table(payment, model, i, 1);
        add_table(overpayment, model, i, 2);
        add_table(debt_balance, model, i, 3);
      }
    }
    if (ui->radioButton_different->isChecked()){
      double payment = amount / term;
      for (int i = 0; i < term; i++) {
        double overpayment = debt_balance * bid;
        debt_balance = debt_balance - payment;
        sum_overpayment += overpayment;
        double sum_payment = payment + overpayment;

        add_table(sum_payment, model, i, 0);
        add_table(payment, model, i, 1);
        add_table(overpayment, model, i, 2);
        add_table(debt_balance, model, i, 3);
      }
    }

    total = sum_overpayment + amount;
    ui->lineEdit_overpayment->setText(QString::number(sum_overpayment, 'f', 2));
    ui->lineEdit_total->setText(QString::number(total, 'f', 2));

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();

}

