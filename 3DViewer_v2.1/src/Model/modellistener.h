#ifndef MODELLISTENER_H
#define MODELLISTENER_H

#include <vector>

#include "normal.h"
#include "texture.h"
#include "vertex.h"

namespace s21 {
class ModelListener {
 public:
  virtual void updateModel(std::vector<int> indexes_,
                           std::vector<SingleVertex> vertexesCoords_,
                           std::vector<SingleTexture> textureCoords_,
                           std::vector<SingleNormal> normals_) = 0;
};
}  // namespace s21
#endif  // MODELLISTENER_H
