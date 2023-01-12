#include "model.h"

namespace s21 {
Model::Model(std::string expression) {
  clearStack();
  parser(expression);
  polish();
}

Model::Model(const Model &other)
    : inputStack_(other.inputStack_), polishStack_(other.polishStack_) {}

void Model::clearStack() {
  inputStack_.clear();
  polishStack_.clear();
}

double Model::expressionCalc(double x) {
  std::list<Token> calcStack;
  double result = 0, num1 = 0, num2 = 0;
  for (auto it = polishStack_.begin(); it != polishStack_.end(); it++) {
    switch ((*it).getType()) {
      case Token::VALUE:
        calcStack.push_front(*it);
        break;
      case Token::UNKNOWN_X:
        (*it) = Token(x);
        calcStack.push_front(*it);
        break;
      case Token::OPERATION:
        if (!calcStack.empty() &&
            (calcStack.front().getType() == Token::VALUE ||
             calcStack.front().getType() == Token::UNKNOWN_X)) {
          num1 = calcStack.front().getValue();
          calcStack.pop_front();
          if (!calcStack.empty() &&
              calcStack.front().getType() == Token::VALUE) {
            num2 = calcStack.front().getValue();
            calcStack.pop_front();
            calcStack.push_front(
                Token(calcOperation(num1, num2, (*it).getOperation())));  // ???
          } else {
            throw std::runtime_error("WRONG EXPRESSION: Num2 doesn't exist");
          }
        } else {
          throw std::runtime_error("WRONG EXPRESSION: Num1 doesn't exist");
        }
        break;
      case Token::FUNCTION:
        if (!calcStack.empty() && calcStack.front().getType() == Token::VALUE) {
          num1 = calcStack.front().getValue();
          calcStack.pop_front();
        } else {
          throw std::runtime_error("WRONG EXPRESSION: Check function");
        }
        calcStack.push_front(Token(calcFunction(num1, (*it).getOperation())));
        break;
    }
  }
  if (!calcStack.empty() && calcStack.front().getType() == Token::VALUE) {
    result = calcStack.front().getValue();
    calcStack.pop_front();
    if (!calcStack.empty()) {
      throw std::runtime_error("WRONG EXPRESSION: Check operations");
    }
  } else {
    throw std::runtime_error("WRONG EXPRESSION: Enter an expression");
  }
  return result;
}

void Model::parseNumber(std::string &expr, int &exprIt, bool unary) {
  int dot = 0;
  std::string buff = "";
  if (unary) {
    buff.push_back(expr[exprIt - 1]);
  }
  while (NUMBER.find_first_of(expr[exprIt]) != std::string::npos) {
    if (expr[exprIt] == '.') {
      dot++;
      if (expr.length() < 2 ||
          NUMBER.find_first_of(expr[exprIt - 1]) == std::string::npos) {
        throw std::runtime_error(
            "Wrong input: Incorrect value of the floating point number");
      }
    }
    buff.push_back(expr[exprIt]);
    exprIt++;
    if (expr[exprIt] == 'e') {
      buff.push_back(expr[exprIt]);
      exprIt++;
      if (expr[exprIt] == '-' || expr[exprIt] == '+') {
        buff.push_back(expr[exprIt]);
        exprIt++;
      }
    }
  }
  if (dot > 1) {
    throw std::runtime_error("Wrong input: Extra point");
  }
  inputStack_.push_back(Token(std::stod(buff)));
}

void Model::parseOperation(std::string const &expr, int &exprIt, int &bracket) {
  if (expr[exprIt] == '(') bracket++;
  if (expr[exprIt] == ')') bracket--;
  if (bracket < 0) {
    throw std::runtime_error(
        "WRONG EXPRESSION: Bracket are incorrectly placed");
  }
  char operation = expr[exprIt];
  exprIt++;
  inputStack_.push_back(Token(operation));
}

void Model::parseFunction(std::string &expr, int &exprIt, bool unary) {
  std::string func = "\0";
  if (unary) {
    inputStack_.push_back(Token(-1.));
    inputStack_.push_back(Token('*'));
  }
  while (TRIGFUNC.find_first_of(expr[exprIt]) != std::string::npos) {
    func.push_back(expr[exprIt]);
    exprIt++;
  }
  if (expr[exprIt] == '(') {
    inputStack_.push_back(Token(func));
  } else {
    throw std::runtime_error(
        "WRONG EXPRESSION: Missing "
        "(");
  }
}

void Model::parseX(int &exprIt, bool unary) {
  if (unary) {
    inputStack_.push_back(Token(-1.));
    inputStack_.push_back(Token('*'));
  }
  inputStack_.push_back(Token('x'));
  exprIt++;
}

void Model::parseMod(int &exprIt) {
  exprIt += 3;
  inputStack_.push_back(Token('m'));
}

void Model::parser(std::string &expr) {
  int len = expr.length() - 1;
  int exprIt = 0;
  int bracket = 0;

  while (exprIt <= len) {
    bool unary = false;
    if (expr[exprIt] == ' ') {
      exprIt++;
    }
    if ((exprIt == 0 && expr[exprIt] == '-') ||
        (exprIt > 0 && expr[exprIt - 1] == '(' && expr[exprIt] == '-')) {
      exprIt++;
      unary = true;
    }
    if ((exprIt == 0 && expr[exprIt] == '+') ||
        (exprIt > 0 && expr[exprIt - 1] == '(' && expr[exprIt] == '+')) {
      exprIt++;
    }
    if (NUMBER.find(expr[exprIt]) != std::string::npos) {
      parseNumber(expr, exprIt, unary);
    } else if (SIGN.find(expr[exprIt]) != std::string::npos) {
      parseOperation(expr, exprIt, bracket);
    } else if (TRIGFUNC.find(expr[exprIt]) != std::string::npos) {
      parseFunction(expr, exprIt, unary);
    } else if (expr[exprIt] == 'x') {
      parseX(exprIt, unary);
    } else if (expr[exprIt] == 'm' && expr[exprIt + 1] == 'o' &&
               expr[exprIt + 2] == 'd') {
      parseMod(exprIt);
    } else {
      throw std::runtime_error("WRONG EXPRESSION: Invalid character");
    }
  }
  if (bracket != 0) {
    throw std::runtime_error(
        "WRONG EXPRESSION: Bracket are incorrectly placed");
  }
}

void Model::polish() {
  std::list<Token> operationStack;
  while (!inputStack_.empty()) {
    Token last = inputStack_.front();
    inputStack_.pop_front();
    if (last.getType() == Token::VALUE || last.getType() == Token::UNKNOWN_X) {
      polishStack_.push_front(last);
    } else if (last.getType() == Token::FUNCTION) {
      operationStack.push_front(last);
    } else if (last.getType() == Token::OPERATION && last.getPriority() >= 0) {
      if (!operationStack.empty()) {
        while (!operationStack.empty() &&
               operationStack.front().getPriority() >= last.getPriority()) {
          stackEntry(operationStack);
        }
        operationStack.push_front(last);
      } else {
        operationStack.push_front(last);
      }
    } else if (last.getOperation() == '(') {
      operationStack.push_front(last);
    } else if (last.getOperation() == ')') {
      if (!operationStack.empty()) {
        while (!operationStack.empty() &&
               operationStack.front().getOperation() != '(') {
          stackEntry(operationStack);
        }
        if (!operationStack.empty() &&
            operationStack.front().getOperation() == '(') {
          operationStack.pop_front();
        }
        if (!operationStack.empty() &&
            operationStack.front().getType() == Token::FUNCTION) {
          stackEntry(operationStack);
        }
      }
    }
  }
  while (!operationStack.empty()) {
    if (operationStack.front().getOperation() == '(') {
      throw std::runtime_error("WRONG EXPRESSION: Missing bracket");
    }
    stackEntry(operationStack);
  }
  polishStack_.reverse();
}

void Model::stackEntry(std::list<Token> &operationStack) {
  polishStack_.push_front(operationStack.front());
  operationStack.pop_front();
}

double Model::calcOperation(double n1, double n2, char oper) {
  double res = 0;
  switch (oper) {
    case '+':
      res = n2 + n1;
      break;
    case '-':
      res = n2 - n1;
      break;
    case '*':
      res = n2 * n1;
      break;
    case '/':
      res = n2 / n1;
      break;
    case '^':
      res = pow(n2, n1);
      break;
    case 'm':
      res = fmod(n2, n1);
      break;
  }
  return res;
}

double Model::calcFunction(double n, char func) {
  double res = 0;
  switch (func) {
    case 'c':
      res = cos(n);
      break;
    case 's':
      res = sin(n);
      break;
    case 't':
      res = tan(n);
      break;
    case 'o':
      res = acos(n);
      break;
    case 'i':
      res = asin(n);
      break;
    case 'a':
      res = atan(n);
      break;
    case 'q':
      res = sqrt(n);
      break;
    case 'n':
      res = log(n);
      break;
    case 'g':
      res = log10(n);
      break;
  }
  return res;
}
}  // namespace s21
