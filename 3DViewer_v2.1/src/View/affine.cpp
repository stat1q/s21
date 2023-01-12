#include "affine.h"

namespace s21 {

Affine::Affine() {}

void Affine::transformModelViewMatrix() {
  modelViewMatrix.setToIdentity();
  modelViewMatrix.translate(m_translate);
  modelViewMatrix.rotate(m_rotation);
  modelViewMatrix.scale(m_scale);
}

void Affine::set_move_x(float newMowe) {
  float bias = m_translate.x() + newMowe;
  m_translate.setX(bias);
}

void Affine::set_move_y(float newMowe) {
  float bias = m_translate.y() + newMowe;
  m_translate.setY(bias);
}

void Affine::set_move_z(float newMowe) {
  float bias = m_translate.z() + newMowe;
  m_translate.setZ(bias);
}

void Affine::set_rotation_x(float angle) {
  m_rotation = QQuaternion::fromAxisAndAngle(1, 0, 0, angle) * m_rotation;
}

void Affine::set_rotation_y(float angle) {
  m_rotation = QQuaternion::fromAxisAndAngle(0, 1, 0, angle) * m_rotation;
}

void Affine::set_rotation_z(float angle) {
  m_rotation = QQuaternion::fromAxisAndAngle(0, 0, 1, angle) * m_rotation;
}

void Affine::set_scalePlus(float newScale) { m_scale *= newScale; }

void Affine::set_scaleMinus(float newScale) { m_scale /= newScale; }

void Affine::set_resetTransform() {
  m_translate = QVector3D(0, 0, -3);
  m_rotation = QQuaternion::fromAxisAndAngle(0, 0, 0, 0);
  m_scale = m_scale_def;
}

const QMatrix4x4 &Affine::getModelViewMatrix() { return modelViewMatrix; }

void Affine::setModelViewMatrix(QMatrix4x4 &newModelViewMatrix) {
  modelViewMatrix = newModelViewMatrix;
}

const QQuaternion &Affine::getRotation() const { return m_rotation; }

void Affine::setRotation(const QQuaternion &newRotation) {
  m_rotation = newRotation;
}

QVector3D &Affine::getTranslate() { return m_translate; }

void Affine::setTranslate(const QVector3D &newTranslate) {
  m_translate = newTranslate;
}

void Affine::setScale(float newScale) { m_scale = newScale; }

float Affine::getScale() const { return m_scale; }

float Affine::getScale_factor() const { return scale_factor_; }

void Affine::setScale_factor(float newScale_factor) {
  scale_factor_ = newScale_factor;
}

void Affine::setScale_def(float newScale_def) { m_scale_def = newScale_def; }

}  // namespace s21
