#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QApplication>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QPainter>
#include <QWidget>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "../settings.h"
#include "adapter.h"
#include "affine.h"
#include "vertexesdatas.h"
#include "viewupdatelistener.h"

namespace s21 {
class GLWidget : public QOpenGLWidget,
                 protected QOpenGLFunctions,
                 public ViewUpdateListener {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

  void setTypeLine();
  void setTypeVertex();
  void projectionSelect();
  void paintMap(QString textFilename);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void initShaders();
  void initShadersFlat();
  void initShadersFrame();
  void initShadersVertex();
  void shadersBind(QMatrix4x4 modelMatrix);
  void drawVertex(QMatrix4x4 modelMatrix);
  void drawModel();
  void changeObjectDisplayType(int index);
  void buffering(QVector<VertexData> vertexesData, QVector<GLuint> indexes);

 public:
  void applyTexture(QString &filePath);
  void offTexture();
  s21::Affine &getAffine();

 private:
  QMatrix4x4 m_projectionMatrix;  // модельно видовая матрица
  QOpenGLShaderProgram m_program;  // шейдерная программа
  QOpenGLShaderProgram m_programPoints;

  QOpenGLBuffer m_arrayBuffer;  // буфер для координат точки
  QOpenGLBuffer m_indexBuffer;

  QVector<QVector4D> m_vertexes_;  // заполняются из адаптера!
  QVector2D m_mousePosition;  // позищия мышки при клике
  QVector3D m_mouseModelPosition_;
  s21::Settings &settings_ = s21::Settings::getInstance();
  s21::Affine affine_;
  QOpenGLTexture *m_texture = nullptr;
  int checkNormalCoords = 1;

  QVector<QVector2D> texturesCoords_;

 public:
  void updateView(QVector<VertexData> vertexesData,
                  QVector<GLuint> indexes) override;
  void updateScale(float scale, float scaleDef, float scaleFactor) override;
};
}  // namespace s21

#endif  // GLWIDGET_H
