#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/parser.h"

namespace s21 {
class Controller {
 private:
  Parser model_;

 public:
  void callParser(std::string fileName);
  int getVertexCount();
  int getFlatCount();
  Parser &getModel();
  void clearModel();
};
}  // namespace s21
#endif  // CONTROLLER_H
