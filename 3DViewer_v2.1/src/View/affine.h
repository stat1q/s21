#ifndef AFFINE_H
#define AFFINE_H

#include "../settings.h"
#include "QtGui/qmatrix4x4.h"
#include "QtGui/qvectornd.h"

namespace s21 {
class Affine {
 public:
  Affine();
  void transformModelViewMatrix();
  void set_move_x(float newMowe);
  void set_move_y(float newMowe);
  void set_move_z(float newMowe);
  void set_rotation_x(float angle);
  void set_rotation_y(float angle);
  void set_rotation_z(float angle);
  void set_scalePlus(float newScale);
  void set_scaleMinus(float newScale);
  void set_resetTransform();
  const QMatrix4x4 &getModelViewMatrix();
  void setModelViewMatrix(QMatrix4x4 &newModelViewMatrix);
  const QQuaternion &getRotation() const;
  void setRotation(const QQuaternion &newRotation);
  QVector3D &getTranslate();
  void setTranslate(const QVector3D &newTranslate);
  void setScale(float newScale);
  float getScale() const;
  float getScale_factor() const;
  void setScale_factor(float newScale_factor);
  void setScale_def(float newScale_def);

 private:
  QMatrix4x4 modelViewMatrix;
  QQuaternion m_rotation;
  QVector3D m_translate;
  float m_scale = 1;
  float m_scale_def = 1;
  float scale_factor_ = 1;
};
}  // namespace s21

#endif  // AFFINE_H
