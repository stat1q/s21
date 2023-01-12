#include "texture.h"

namespace s21 {

SingleTexture::SingleTexture(const std::vector<double> &texture)
    : oneTextureCoords_(texture) {}

std::vector<double> SingleTexture::getOneTextureCoords() {
  return oneTextureCoords_;
}

}  // namespace s21
