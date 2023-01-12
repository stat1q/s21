#pragma once
#include <iostream>
#include <list>
#include <string>

namespace s21 {
class Token {
 public:
  typedef enum {
    VALUE = 0,
    OPERATION = 1,
    FUNCTION = 2,
    UNKNOWN_X = 3
  } symbol_type;

 private:
  double value_;
  char operation_;
  int priority_;
  symbol_type symb_type_;

 public:
  explicit Token(double value);
  explicit Token(char operation);
  explicit Token(std::string &function);
  ~Token() {}

  double getValue();
  char getOperation();
  int getType();
  int getPriority();

  int operationPriority(char oper);
  char checkTrigFunc(std::string const &func);
};
}  // namespace s21
