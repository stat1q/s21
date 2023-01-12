#include "glwidget.h"
namespace s21 {
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_indexBuffer(QOpenGLBuffer::IndexBuffer) {
  this->setFocusPolicy(Qt::ClickFocus);
}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.2, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  initShadersFrame();
  initShadersVertex();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
  float aspect = (float)w / (float)(h ? h : 1);
  m_projectionMatrix.setToIdentity();
  if (!settings_.getProjectionType()) {
    m_projectionMatrix.perspective(45, aspect, 0.1f, 1000.0f);
  } else {
    const double rect = 1.0;
    m_projectionMatrix.ortho(-rect * aspect, rect * aspect, -rect, rect, 0.01f,
                             100.0f);
  }
}

void GLWidget::paintGL() {
  glClearColor(settings_.getColorBG().x(), settings_.getColorBG().y(),
               settings_.getColorBG().z(), settings_.getColorBG().w());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  changeObjectDisplayType(settings_.getObjectDisplayType());
  glLineWidth(settings_.getLineWidth());
  setTypeLine();
  affine_.transformModelViewMatrix();
  QMatrix4x4 modelMatrix;
  modelMatrix.setToIdentity();
  shadersBind(modelMatrix);
  drawModel();
  drawVertex(modelMatrix);
}

void GLWidget::drawModel() {
  m_arrayBuffer.bind();
  m_indexBuffer.bind();
  int offset = 0;
  int vertLoc = m_program.attributeLocation("a_position");
  m_program.enableAttributeArray(vertLoc);
  m_program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3,
                               sizeof(VertexData));
  offset += sizeof(QVector3D);
  int texLoc = m_program.attributeLocation("a_texcoord");
  m_program.enableAttributeArray(texLoc);
  m_program.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));
  offset += sizeof(QVector2D);
  int normLoc = m_program.attributeLocation("a_normal");
  m_program.enableAttributeArray(normLoc);
  m_program.setAttributeBuffer(normLoc, GL_FLOAT, offset, 3,
                               sizeof(VertexData));
  m_program.setUniformValue("color", settings_.getColorLine());

  glDrawElements(GL_TRIANGLES, m_indexBuffer.size() / sizeof(GLuint),
                 GL_UNSIGNED_INT, nullptr);
}

void GLWidget::shadersBind(QMatrix4x4 modelMatrix) {
  if (m_texture != nullptr) {
    m_texture->bind(0);
  }
  m_program.bind();
  m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
  m_program.setUniformValue("u_vievMatrix", affine_.getModelViewMatrix());
  m_program.setUniformValue("u_modelMatrix", modelMatrix);
  m_program.setUniformValue("u_ligthtPosition", settings_.getLigthtPosition());
  m_program.setUniformValue("u_ligthtColor", settings_.getLigthtColor());
  m_program.setUniformValue("u_lightPower", 1.00f);
  m_program.setUniformValue("u_specelarFactor", settings_.getLightPower());
  m_program.setUniformValue("n_shift", checkNormalCoords);
  m_program.setUniformValue("a_shift", settings_.getModelFilltype());
}

void GLWidget::drawVertex(QMatrix4x4 modelMatrix) {
  setTypeVertex();
  if (settings_.getVertexType() != 0) {
    m_programPoints.bind();
    m_programPoints.setUniformValue("u_projectionMatrixP", m_projectionMatrix);
    m_programPoints.setUniformValue("u_vievMatrixP",
                                    affine_.getModelViewMatrix());
    m_programPoints.setUniformValue("u_modelMatrixP", modelMatrix);
    int vertLoc = m_programPoints.attributeLocation("a_positionP");
    m_programPoints.enableAttributeArray(vertLoc);
    m_programPoints.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3,
                                       sizeof(VertexData));

    m_programPoints.setUniformValue("color", settings_.getColorVertex());
    glPointSize(settings_.getVertexWidth());
    glDrawElements(GL_POINTS, m_indexBuffer.size() / sizeof(GLuint),
                   GL_UNSIGNED_INT, nullptr);
  }
}

void GLWidget::changeObjectDisplayType(int index) {
  if (index == 0) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    initShadersFrame();
    update();
  } else if (index == 1) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    initShadersFlat();
    update();
  } else if (index == 2) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    initShaders();
    update();
  }
}

void GLWidget::initShadersVertex() {
  m_programPoints.removeAllShaders();
  if (!m_programPoints.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               ":/vshader_points.vsh")) {
    close();
  }
  if (!m_programPoints.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               ":/fshader_points.fsh")) {
    close();
  }
  if (!m_programPoints.link()) {
    close();
  }
}

void GLWidget::initShadersFlat() {
  m_program.removeAllShaders();
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/vshader_flat.vsh")) {
    close();
  }
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/fshader_flat.fsh")) {
    close();
  }
  if (!m_program.link()) {
    close();
  }
}

void GLWidget::initShaders() {
  m_program.removeAllShaders();
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/vshader.vsh")) {
    close();
  }
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/fshader.fsh")) {
    close();
  }
  if (!m_program.link()) {
    close();
  }
}

void GLWidget::initShadersFrame() {
  m_program.removeAllShaders();
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/vshader_frame.vsh")) {
    close();
  }
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/fshader_frame.fsh")) {
    close();
  }
  if (!m_program.link()) {
    close();
  }
}

void GLWidget::buffering(QVector<VertexData> vertexesData,
                         QVector<GLuint> indexes) {
  m_arrayBuffer.create();
  m_arrayBuffer.bind();
  m_arrayBuffer.allocate(vertexesData.constData(),
                         vertexesData.size() * sizeof(VertexData));
  m_arrayBuffer.release();

  m_indexBuffer.create();
  m_indexBuffer.bind();
  m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
  m_indexBuffer.release();
}

void GLWidget::paintMap(QString textFilename) {
  if (!texturesCoords_.isEmpty()) {
    QPoint point(0, 0);
    QImage image(textFilename);
    QPainter paint(&image);
    int height = image.height();
    int width = image.width();
    paint.setPen(Qt::red);
    paint.drawImage(point, image);

    for (int i = 1; i < (int)texturesCoords_.size(); i = i + 3) {
      paint.drawLine(width * texturesCoords_[i].x(),
                     height - (height * texturesCoords_[i].y()),
                     width * texturesCoords_[i - 1].x(),
                     height - (height * texturesCoords_[i - 1].y()));
    }
    paint.end();
    QString fileType = "bmp";
    QString fileName = QDate::currentDate().toString() + " " +
                       QTime::currentTime().toString() + "." + fileType;
    QString path = QFileDialog::getSaveFileName(
        this, tr("Save file"), SRCDIR "screenshots/" + fileName,
        "Images (*" + fileType + ")");
    if (!path.isEmpty()) {
      image.save(path);
    }
  }
}

void GLWidget::applyTexture(QString &filePath) {
  settings_.setModelFilltype(1);
  m_texture = new QOpenGLTexture(QImage(filePath).mirrored());
  m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
  m_texture->setMinificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::Repeat);
  update();
}

void GLWidget::offTexture() {
  settings_.setModelFilltype(0);
  update();
}

s21::Affine &GLWidget::getAffine() { return affine_; }

void GLWidget::updateView(QVector<VertexData> vertexesData,
                          QVector<GLuint> indexes) {
  for (QVector<VertexData>::iterator it = vertexesData.begin();
       it != vertexesData.end(); ++it) {
    texturesCoords_.push_back((*it).textcoord);
  }
  buffering(vertexesData, indexes);
  if (vertexesData[0].normal.isNull()) {
    checkNormalCoords = 0;
  } else {
    checkNormalCoords = 1;
  }
}

void GLWidget::updateScale(float scale, float scaleDef, float scaleFactor) {
  affine_.set_resetTransform();
  affine_.setScale(scale);
  affine_.setScale_def(scaleDef);
  affine_.setScale_factor(scaleFactor);
}

void GLWidget::setTypeLine() {
  if (settings_.getLineType()) {
    glEnable(GL_LINE_STIPPLE), glLineStipple(10, 0xAAAA);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLWidget::setTypeVertex() {
  m_program.setUniformValue("color", settings_.getColorVertex());
  glPointSize(settings_.getVertexWidth());
  if (settings_.getVertexType() == 1) glDisable(GL_POINT_SMOOTH);
  if (settings_.getVertexType() == 2) glEnable(GL_POINT_SMOOTH);
}

void GLWidget::projectionSelect() {
  resizeGL(width(), height());
  update();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton ||
      event->buttons() == Qt::RightButton) {
    m_mousePosition = QVector2D(event->position());
  }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    QVector2D diff = QVector2D(event->position()) - m_mousePosition;
    m_mousePosition = QVector2D(event->position());
    float angle = diff.length() / 2.0;
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);
    affine_.setRotation(QQuaternion::fromAxisAndAngle(axis, angle) *
                        affine_.getRotation());
  } else if (event->buttons() == Qt::RightButton) {
    float width = (float)size().width() / 2;
    float height = (float)size().height() / 2;
    QVector3D m_mouseModelPosition_ =
        QVector3D((event->position().x() - width) / 500,
                  (event->position().y() - height) / -500, -3);
    affine_.setTranslate(m_mouseModelPosition_);
  }
  update();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 8;
  affine_.setScale(affine_.getScale() +
                   (float)numDegrees.ry() / (900 * affine_.getScale_factor()));
  update();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
    affine_.getTranslate().setX(affine_.getTranslate().x() - 0.05);
  } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
    affine_.getTranslate().setX(affine_.getTranslate().x() + 0.05);
  } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
    affine_.getTranslate().setY(affine_.getTranslate().y() + 0.05);
  } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
    affine_.getTranslate().setY(affine_.getTranslate().y() - 0.05);
  }
  update();
}
}  // namespace s21
