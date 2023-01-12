#pragma once

#include "model.h"

namespace s21 {
class Controller {
 private:
  Model model_;
  std::string expr_;
  bool plotState_ = false;

 public:
  Controller() {}
  Controller(const Controller &other);
  ~Controller() {}

  double getResult(double x);
  void putStringElement(std::string const &element);
  std::string getExpr();
  Model getModel();
  void setPlotState(bool plotState);
  void clearExrp();
  void clearModel();
  void deleteSymbol();
};
}  // namespace s21
