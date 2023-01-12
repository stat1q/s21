#ifndef CREDITCONTROLLER_H
#define CREDITCONTROLLER_H

#include "creditmodel.h"

namespace s21 {
class CreditController {
 public:
  CreditController(double creditSum, int term, double bid, bool annuity);
  CreditController(const CreditController &other);
  ~CreditController();

  CreditController &operator=(const CreditController &other);

  double getSumOverPayment();
  double getTotal();
  QStandardItemModel *getCreditModel();

 private:
  CreditModel *creditModel_ = nullptr;
};
}  // namespace s21

#endif  // CREDITCONTROLLER_H