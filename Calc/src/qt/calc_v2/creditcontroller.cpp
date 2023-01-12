#include "creditcontroller.h"

namespace s21 {
CreditController::CreditController(double creditSum, int term, double bid,
                                   bool annuity) {
  creditModel_ = new CreditModel(creditSum, term, bid, annuity);
}

CreditController::CreditController(const CreditController &other) {
  creditModel_ = new CreditModel(*(other.creditModel_));
}

CreditController &CreditController::operator=(const CreditController &other) {
  if (this != &other) {
    delete creditModel_;
    creditModel_ = new CreditModel(*(other.creditModel_));
  }
  return *this;
}

CreditController::~CreditController() { delete creditModel_; }

double CreditController::getSumOverPayment() {
  return creditModel_->getSumOverPayment();
}

double CreditController::getTotal() { return creditModel_->getTotal(); }

QStandardItemModel *CreditController::getCreditModel() {
  return creditModel_->getCreditModel();
}

}  // namespace s21