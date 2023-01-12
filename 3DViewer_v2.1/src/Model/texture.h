#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <vector>

namespace s21 {
class SingleTexture {
 private:
  std::vector<double> oneTextureCoords_;

 public:
  explicit SingleTexture(const std::vector<double> &texture);
  std::vector<double> getOneTextureCoords();
};
}  // namespace s21
#endif  // TEXTURE_H
