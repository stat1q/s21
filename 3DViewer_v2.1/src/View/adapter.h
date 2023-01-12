#ifndef ADAPTER_H
#define ADAPTER_H

#include <QDebug>
#include <QFile>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QVector>
#include <iostream>
#include <vector>

#include "../Controller/controller.h"
#include "../Model/modellistener.h"
#include "../Model/parser.h"
#include "vertexesdatas.h"
#include "viewupdatelistener.h"

namespace s21 {
class Adapter : public ModelListener {
 public:
  Adapter() {}
  Controller &getController();

  void biasAxistoCenter();
  void acceptAxistoCenter();
  QVector2D autoScale();

 private:
  void flatConvertingForTrianglesDrawing(std::vector<int> &indexes);
  void vertexesConvert(std::vector<SingleVertex> &vertexesCoords);
  void normalsConvert(std::vector<SingleNormal> &normals);
  void texturesConvert(std::vector<SingleTexture> &textureCoords);
  void clearAdapterData();

 private:
  QVector<VertexData> vertexesData_;
  QVector<GLuint> indexes_;

  QVector<QVector3D> vertexes_;
  QVector<QVector3D> normals_;
  QVector<QVector2D> textures_;

  QVector3D setAxistoCenter_;
  QVector3D geomParam_;
  QVector2D a_scale_;

  ViewUpdateListener *updater = nullptr;

 public:
  void updateModel(std::vector<int> indexes_,
                   std::vector<SingleVertex> vertexesCoords_,
                   std::vector<SingleTexture> textureCoords_,
                   std::vector<SingleNormal> normals_);
  void setUpdater(ViewUpdateListener *newUpdater);
};
}  // namespace s21

#endif  // ADAPTER_H
