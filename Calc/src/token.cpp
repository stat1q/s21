#include "token.h"

namespace s21 {
Token::Token(double value)
    : value_(value), operation_('d'), priority_(0), symb_type_(VALUE) {}

Token::Token(char operation) : value_(0), operation_(operation) {
  if (operation == 'x') {
    priority_ = 0;
    symb_type_ = UNKNOWN_X;
  } else if (operation == 'm') {
    priority_ = 3;
    symb_type_ = OPERATION;
  } else {
    priority_ = operationPriority(operation);
    symb_type_ = OPERATION;
  }
}

Token::Token(std::string &function)
    : value_(0),
      operation_(checkTrigFunc(function)),
      priority_(4),
      symb_type_(FUNCTION) {}

int Token::operationPriority(char oper) {
  int priority = 0;
  switch (oper) {
    case '^':
      priority = 3;
      break;
    case '*':
    case '/':
      priority = 2;
      break;
    case '+':
    case '-':
      priority = 1;
      break;
    case '(':
      priority = -1;
      break;
    case ')':
      priority = -2;
      break;
  }
  return priority;
}

char Token::checkTrigFunc(std::string const &func) {
  int i = 0;
  char func_symb = '\0';
  if (func[i] == 'c' && func[i + 1] == 'o' && func[i + 2] == 's') {
    func_symb = 'c';
  } else if (func[i] == 's' && func[i + 1] == 'i' && func[i + 2] == 'n') {
    func_symb = 's';
  } else if (func[i] == 't' && func[i + 1] == 'a' && func[i + 2] == 'n') {
    func_symb = 't';
  } else if (func[i] == 'a' && func[i + 1] == 'c' && func[i + 2] == 'o' &&
             func[i + 3] == 's') {
    func_symb = 'o';
  } else if (func[i] == 'a' && func[i + 1] == 's' && func[i + 2] == 'i' &&
             func[i + 3] == 'n') {
    func_symb = 'i';
  } else if (func[i] == 'a' && func[i + 1] == 't' && func[i + 2] == 'a' &&
             func[i + 3] == 'n') {
    func_symb = 'a';
  } else if (func[i] == 's' && func[i + 1] == 'q' && func[i + 2] == 'r' &&
             func[i + 3] == 't') {
    func_symb = 'q';
  } else if (func[i] == 'l' && func[i + 1] == 'n') {
    func_symb = 'n';
  } else if (func[i] == 'l' && func[i + 1] == 'o' && func[i + 2] == 'g') {
    func_symb = 'g';
  } else {
    throw std::runtime_error("non-existent function");
  }
  return func_symb;
}

double Token::getValue() { return value_; }

char Token::getOperation() { return operation_; }

int Token::getType() { return symb_type_; }

int Token::getPriority() { return priority_; }
}  // namespace s21