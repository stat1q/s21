#include "adapter.h"

namespace s21 {

void Adapter::vertexesConvert(std::vector<SingleVertex> &vertexesCoords) {
  for (std::vector<SingleVertex>::iterator itV = vertexesCoords.begin();
       itV != vertexesCoords.end(); ++itV) {
    vertexes_.append(QVector3D((*itV).getOneVertexCoords()[0],
                               (*itV).getOneVertexCoords()[1],
                               (*itV).getOneVertexCoords()[2]));
  }
}

void Adapter::normalsConvert(std::vector<SingleNormal> &normals) {
  for (std::vector<SingleNormal>::iterator itN = normals.begin();
       itN != normals.end(); ++itN) {
    normals_.append(QVector3D((*itN).getOneNormal()[0],
                              (*itN).getOneNormal()[1],
                              (*itN).getOneNormal()[2]));
  }
}

void Adapter::texturesConvert(std::vector<SingleTexture> &textureCoords) {
  for (std::vector<SingleTexture>::iterator itT = textureCoords.begin();
       itT != textureCoords.end(); ++itT) {
    textures_.append(QVector2D((*itT).getOneTextureCoords()[0],
                               (*itT).getOneTextureCoords()[1]));
  }
}

void Adapter::clearAdapterData() {
  vertexesData_.clear();
  indexes_.clear();
  vertexes_.clear();
  normals_.clear();
  textures_.clear();
}

void Adapter::setUpdater(ViewUpdateListener *newUpdater) {
  updater = newUpdater;
}

void Adapter::updateModel(std::vector<int> indexes,
                          std::vector<SingleVertex> vertexesCoords,
                          std::vector<SingleTexture> textureCoords,
                          std::vector<SingleNormal> normals) {
  clearAdapterData();
  vertexesConvert(vertexesCoords);
  biasAxistoCenter();
  acceptAxistoCenter();
  normalsConvert(normals);
  texturesConvert(textureCoords);

  updater->updateScale(autoScale().x(), autoScale().x(), autoScale().y());
  flatConvertingForTrianglesDrawing(indexes);
  if (updater != nullptr) {
    updater->updateView(vertexesData_, indexes_);
  }
}

void Adapter::flatConvertingForTrianglesDrawing(std::vector<int> &indexes) {
  int itF = 0;
  if (textures_.empty() && normals_.empty()) {
    for (unsigned long i = 0; i < (indexes.size()); ++i) {
      vertexesData_.append(VertexData(vertexes_[indexes[itF] - 1]));
      itF++;
      indexes_.append(indexes_.size());
    }
  } else if (textures_.empty()) {
    for (unsigned long i = 0; i < (indexes.size() / 2); ++i) {
      vertexesData_.append(VertexData(vertexes_[indexes[itF] - 1],
                                      normals_[indexes[itF + 1] - 1]));
      itF += 2;
      indexes_.append(indexes_.size());
    }
  } else if (normals_.empty()) {
    for (unsigned long i = 0; i < (indexes.size() / 2); ++i) {
      vertexesData_.append(VertexData(vertexes_[indexes[itF] - 1],
                                      textures_[indexes[itF + 1] - 1]));
      itF += 2;
      indexes_.append(indexes_.size());
    }
  } else {
    for (unsigned long i = 0; i < (indexes.size() / 3); ++i) {
      vertexesData_.append(VertexData(vertexes_[indexes[itF] - 1],
                                      textures_[indexes[itF + 1] - 1],
                                      normals_[indexes[itF + 2] - 1]));
      itF += 3;
      indexes_.append(indexes_.size());
    }
  }
}

void Adapter::biasAxistoCenter() {
  float x_min = 0;
  float x_max = 0;
  float y_min = 0;
  float y_max = 0;
  float z_min = 0;
  float z_max = 0;
  for (QVector<QVector3D>::iterator itV = vertexes_.begin();
       itV != vertexes_.end(); ++itV) {
    float x = (*itV).x();
    float y = (*itV).y();
    float z = (*itV).z();
    if (itV == vertexes_.begin()) {
      x_min = x;
      x_max = x;
      y_min = y;
      y_max = y;
      z_min = z;
      z_max = z;
    }
    if (x < x_min) {
      x_min = x;
    } else if (x > x_max) {
      x_max = x;
    }
    if (y < y_min) {
      y_min = y;
    } else if (y > y_max) {
      y_max = y;
    }
    if (z < z_min) {
      z_min = z;
    } else if (z > z_max) {
      z_max = z;
    }
  }
  setAxistoCenter_ =
      QVector3D((x_min + x_max) / 2, (y_min + y_max) / 2, (z_min + z_max) / 2);
  geomParam_ = QVector3D((abs(x_min) + abs(x_max)), (abs(y_min) + abs(y_max)),
                         (abs(z_min) + abs(z_max)));
}

void Adapter::acceptAxistoCenter() {
  if (setAxistoCenter_.x() != 0 || setAxistoCenter_.y() != 0) {
    for (auto it = vertexes_.begin(); it != vertexes_.end(); ++it) {
      *it -= setAxistoCenter_;
    }
  }
}

QVector2D Adapter::autoScale() {
  float scaleFactor = geomParam_.x();
  if (scaleFactor < geomParam_.y()) {
    scaleFactor = geomParam_.y();
  }
  a_scale_ = QVector2D(1.5 / (scaleFactor), scaleFactor);
  return a_scale_;
}

}  // namespace s21
