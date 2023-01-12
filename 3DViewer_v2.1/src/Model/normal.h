#ifndef NORMAL_H
#define NORMAL_H

#include <iostream>
#include <vector>

namespace s21 {
class SingleNormal {
 private:
  std::vector<double> oneNormal_;

 public:
  explicit SingleNormal(const std::vector<double> &normal);
  std::vector<double> getOneNormal();
};
}  // namespace s21
#endif  // NORMAL_H
