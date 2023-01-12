#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QVector4D>

#include "QtGui/qmatrix4x4.h"

namespace s21 {

class Settings;

class SettingsDestroyer {
 private:
  Settings *p_instance;

 public:
  ~SettingsDestroyer();
  void initialize(Settings *p);
};

class Settings {
 private:
  static Settings *p_instance;
  static SettingsDestroyer destroyer;

  QString filesettings = SRCDIR "etc/config.ini";

  bool lineType_;
  bool projectionType_;
  uint lineWidth_;
  uint vertexWidth_;
  uint vertexType_;
  QVector4D colorLine_;
  QVector4D colorBG_;
  QVector4D colorVertex_;
  bool autoScale_;
  bool optiScale_;
  bool axioCentering_;

  int objectDisplayType_;
  int modelFilltype_;

  QVector4D ligthtPosition_;
  QVector4D ligthtColor_;
  float lightPower_;

 protected:
  Settings() {}
  Settings(const Settings &);
  Settings &operator=(Settings &);
  ~Settings() {}

  friend class SettingsDestroyer;

 public:
  static Settings &getInstance();
  void SaveInFile();
  void LoadFromFile();

  bool getProjectionType() const;
  void setProjectionType(bool newProjectionType);
  bool getLineType() const;
  void setLineType(bool newLineType);
  uint getLineWidth() const;
  void setLineWidth(uint newLineWidth);
  uint getVertexWidth() const;
  void setVertexWidth(uint newVertexWidth);
  uint getVertexType() const;
  void setVertexType(uint newVertexType);
  QVector4D getColorLine() const;
  void setColorLine(float newX, float newY, float newZ, float newW);
  QVector4D getColorBG() const;
  void setColorBG(float newX, float newY, float newZ, float newW);
  QVector4D getColorVertex() const;
  void setColorVertex(float newX, float newY, float newZ, float newW);

  QVector4D getLigthtPosition() const;
  void setLigthtPosition(float newX, float newY, float newZ, float newW);
  QVector4D getLigthtColor() const;
  void setLigthtColor(float newX, float newY, float newZ, float newW);
  float getLightPower() const;
  void setLightPower(float newLightPower);

  bool getAutoScale() const;
  void setAutoScale(bool newAutoScale);
  bool getOptiScale() const;
  void setOptiScale(bool newOptiScale);
  bool getAxioCentering() const;
  void setAxioCentering(bool newAxioCentering);
  int getObjectDisplayType() const;
  void setObjectDisplayType(int newObjectDisplayType);
  int getModelFilltype() const;
  void setModelFilltype(bool newModelFilltype);
};
}  // namespace s21
#endif  // SETTINGS_H
