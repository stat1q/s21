#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>

namespace s21 {
class SingleVertex {
 private:
  std::vector<double> oneVertexCoords_;

 public:
  explicit SingleVertex(const std::vector<double> &v);
  std::vector<double> getOneVertexCoords();

  void setOneVertexCoords(const std::vector<double> &oneVertexCoords);
  void printVertex();
};
}  // namespace s21
#endif  // VERTEX_H
