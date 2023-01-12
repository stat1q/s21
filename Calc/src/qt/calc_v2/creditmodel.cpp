#include "creditmodel.h"

namespace s21 {
CreditModel::CreditModel(double creditSum, int term, double bid, bool annuity) {
  model_ = new QStandardItemModel();
  sumOverPayment_ = 0.0;  // сумма переплаты
  total_ = 0.0;           // общая сумма выплат

  double monthlyRate = (bid / 12) / 100;  // процентная ставка в месяц
  double balanceDebt = creditSum;  // остаток долга

  if (annuity) {
    double sumPayment =
        roundf(creditSum * (monthlyRate / (1 - pow(1 + monthlyRate, -term))) *
               100) /
        100;
    sumOverPayment_ = sumPayment * term - creditSum;
    for (int i = 0; i < term; i++) {
      double overPayment = balanceDebt * monthlyRate;
      double payment = roundf((sumPayment - overPayment) * 100) / 100;
      balanceDebt -= payment;
      addLine(i, sumPayment, payment, overPayment, balanceDebt);
    }
  } else {
    double payment = creditSum / term;
    for (int i = 0; i < term; i++) {
      double overPayment = balanceDebt * monthlyRate;
      balanceDebt -= payment;
      sumOverPayment_ += overPayment;
      double sumPayment = payment + overPayment;
      addLine(i, sumPayment, payment, overPayment, balanceDebt);
    }
  }
  total_ = sumOverPayment_ + creditSum;
}

CreditModel::CreditModel(const CreditModel &other) {
  model_ = new QStandardItemModel(other.model_);
  sumOverPayment_ = other.sumOverPayment_;
  total_ = other.total_;
}

CreditModel &CreditModel::operator=(const CreditModel &other) {
  if (this != &other) {
    model_ = new QStandardItemModel(other.model_);
    sumOverPayment_ = other.sumOverPayment_;
    total_ = other.total_;
  }
  return *this;
}

CreditModel::~CreditModel() { delete model_; }

void CreditModel::addTable(double d, int i, int j) {
  QStandardItem *item = new QStandardItem(QString::number(d, 'f', 2));
  model_->setItem(i, j, item);
}

void CreditModel::addLine(int i, double a, double b, double c, double d) {
  addTable(a, i, 0);
  addTable(b, i, 1);
  addTable(c, i, 2);
  addTable(d, i, 3);
}

double CreditModel::getSumOverPayment() { return sumOverPayment_; }

double CreditModel::getTotal() { return total_; }

QStandardItemModel *CreditModel::getCreditModel() { return this->model_; }
}  // namespace s21
