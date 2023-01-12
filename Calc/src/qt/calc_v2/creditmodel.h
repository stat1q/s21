#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <QStandardItemModel>

namespace s21 {
class CreditModel {
 public:
  CreditModel(double creditSum, int term, double bid, bool annuity);
  CreditModel(const CreditModel &other);
  ~CreditModel();

  CreditModel &operator=(const CreditModel &other);

  void addTable(double d, int i, int j);
  void addLine(int i, double a, double b, double c, double d);

  double getSumOverPayment();
  double getTotal();
  QStandardItemModel *getCreditModel();

 private:
  QStandardItemModel *model_;
  double sumOverPayment_;
  double total_;
};
}  // namespace s21

#endif  // CREDITMODEL_H
