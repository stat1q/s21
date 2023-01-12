#ifndef VERTEXESDATAS_H
#define VERTEXESDATAS_H

#include <QVector3D>

namespace s21 {
struct VertexData {
  VertexData() {}
  VertexData(QVector3D p, QVector2D t, QVector3D n)
      : position(p), textcoord(t), normal(n) {}
  VertexData(QVector3D p, QVector3D n) : position(p), normal(n) {}
  VertexData(QVector3D p, QVector2D t) : position(p), textcoord(t) {}
  VertexData(QVector3D p) : position(p) {}
  QVector3D position;
  QVector2D textcoord;
  QVector3D normal;
};

class VertexesDatas {
 public:
  VertexesDatas() {}
};

}  // namespace s21
#endif  // VERTEXESDATAS_H
