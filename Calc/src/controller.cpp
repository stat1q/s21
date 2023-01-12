#include "controller.h"

namespace s21 {
Controller::Controller(const Controller &other)
    : model_(other.model_), expr_(other.expr_), plotState_(false) {}

void Controller::putStringElement(std::string const &element) {
  expr_ += element;
}

std::string Controller::getExpr() { return expr_; }

void Controller::clearModel() { model_.clearStack(); }

void Controller::setPlotState(bool plotState) { plotState_ = plotState; }

void Controller::clearExrp() { expr_ = ""; }

void Controller::deleteSymbol() {
  if (expr_ != "\0") {
    expr_.pop_back();
  }
}

double Controller::getResult(double x) {
  model_.parser(expr_);
  model_.polish();
  double result = model_.expressionCalc(x);
  if (!plotState_) {
    model_.clearStack();
  }
  return result;
}
}  // namespace s21
