#include "vertex.h"

namespace s21 {

SingleVertex::SingleVertex(const std::vector<double> &v)
    : oneVertexCoords_(v) {}

std::vector<double> SingleVertex::getOneVertexCoords() {
  return oneVertexCoords_;
}

void SingleVertex::setOneVertexCoords(
    const std::vector<double> &oneVertexCoords) {
  oneVertexCoords_ = oneVertexCoords;
}

void SingleVertex::printVertex() {
  std::cout << oneVertexCoords_[0] << " " << oneVertexCoords_[1] << " "
            << oneVertexCoords_[2] << std::endl;
}

}  // namespace s21