#pragma once
#include <cmath>

#include "token.h"

namespace s21 {
class Model {
 private:
  std::list<Token> inputStack_;
  std::list<Token> polishStack_;

  std::string const NUMBER = "0123456789.";
  std::string const SIGN = "+-*/^()";
  std::string const TRIGFUNC = "sincotaqrlg";

 public:
  Model() {}
  explicit Model(std::string expression);
  explicit Model(const Model &other);
  ~Model() {}

  void clearStack();
  double expressionCalc(double x);

 private:
  void parseNumber(std::string &expr, int &exprIt, bool unary);
  void parseOperation(std::string const &expr, int &exprIt, int &bracket);
  void parseFunction(std::string &expr, int &exprIt, bool unary);
  void parseX(int &exprIt, bool unary);
  void parseMod(int &exprIt);

  void stackEntry(std::list<Token> &operationStack);
  double calcOperation(double n1, double n2, char oper);
  double calcFunction(double n, char func);

 public:
  void parser(std::string &expr);
  void polish();
};
}  // namespace s21
