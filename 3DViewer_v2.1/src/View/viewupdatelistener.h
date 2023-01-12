#ifndef VIEWUPDATELISTENER_H
#define VIEWUPDATELISTENER_H

#include <QOpenGLBuffer>

#include "vertexesdatas.h"

namespace s21 {
class ViewUpdateListener {
 public:
  virtual void updateView(QVector<VertexData> vertexesData,
                          QVector<GLuint> indexes) = 0;
  virtual void updateScale(float scale, float scaleDef, float scaleFactor) = 0;
};

}  // namespace s21
#endif  // VIEWUPDATELISTENER_H
