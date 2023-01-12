#include "normal.h"

namespace s21 {

SingleNormal::SingleNormal(const std::vector<double> &normal)
    : oneNormal_(normal) {}

std::vector<double> SingleNormal::getOneNormal() { return oneNormal_; }

}  // namespace s21
