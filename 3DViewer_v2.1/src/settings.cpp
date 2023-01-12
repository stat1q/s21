#include "settings.h"

#include <iostream>

namespace s21 {

Settings *Settings::p_instance = 0;
SettingsDestroyer Settings::destroyer;

SettingsDestroyer::~SettingsDestroyer() { delete p_instance; }
void SettingsDestroyer::initialize(Settings *p) { p_instance = p; }

int Settings::getObjectDisplayType() const { return objectDisplayType_; }

void Settings::setObjectDisplayType(int newObjectDisplayType) {
  objectDisplayType_ = newObjectDisplayType;
}

int Settings::getModelFilltype() const { return modelFilltype_; }

void Settings::setModelFilltype(bool newModelFilltype) {
  modelFilltype_ = newModelFilltype;
}

Settings &Settings::getInstance() {
  if (!p_instance) {
    p_instance = new Settings();
    destroyer.initialize(p_instance);
  }
  return *p_instance;
}

bool Settings::getProjectionType() const { return projectionType_; }

void Settings::setProjectionType(bool newProjectionType) {
  projectionType_ = newProjectionType;
}

bool Settings::getLineType() const { return lineType_; }

void Settings::setLineType(bool newLineType) { lineType_ = newLineType; }

uint Settings::getLineWidth() const { return lineWidth_; }

void Settings::setLineWidth(uint newLineWidth) { lineWidth_ = newLineWidth; }

uint Settings::getVertexWidth() const { return vertexWidth_; }

void Settings::setVertexWidth(uint newVertexWidth) {
  vertexWidth_ = newVertexWidth;
}

uint Settings::getVertexType() const { return vertexType_; }

void Settings::setVertexType(uint newVertexType) {
  vertexType_ = newVertexType;
}

QVector4D Settings::getColorLine() const { return colorLine_; }

void Settings::setColorLine(float newX, float newY, float newZ, float newW) {
  colorLine_ = QVector4D(newX, newY, newZ, newW);
}

QVector4D Settings::getColorBG() const { return colorBG_; }

void Settings::setColorBG(float newX, float newY, float newZ, float newW) {
  colorBG_ = QVector4D(newX, newY, newZ, newW);
}

QVector4D Settings::getColorVertex() const { return colorVertex_; }

void Settings::setColorVertex(float newX, float newY, float newZ, float newW) {
  colorVertex_ = QVector4D(newX, newY, newZ, newW);
}

bool Settings::getAutoScale() const { return autoScale_; }

void Settings::setAutoScale(bool newAutoScale) { autoScale_ = newAutoScale; }

bool Settings::getOptiScale() const { return optiScale_; }

void Settings::setOptiScale(bool newOptiScale) { optiScale_ = newOptiScale; }

bool Settings::getAxioCentering() const { return axioCentering_; }

void Settings::setAxioCentering(bool newAxioCentering) {
  axioCentering_ = newAxioCentering;
}

QVector4D Settings::getLigthtPosition() const { return ligthtPosition_; }
void Settings::setLigthtPosition(float newX, float newY, float newZ,
                                 float newW) {
  ligthtPosition_ = QVector4D(newX, newY, newZ, newW);
}
QVector4D Settings::getLigthtColor() const { return ligthtColor_; }
void Settings::setLigthtColor(float newX, float newY, float newZ, float newW) {
  ligthtColor_ = QVector4D(newX, newY, newZ, newW);
}
float Settings::getLightPower() const { return lightPower_; }
void Settings::setLightPower(float newlightPower) {
  lightPower_ = newlightPower;
}

void Settings::SaveInFile() {
  qDebug() << "Save";
  QSettings saveSettings(filesettings, QSettings::IniFormat);
  saveSettings.setValue("lineType", lineType_);
  saveSettings.setValue("projectionType", projectionType_);
  saveSettings.setValue("line_width", lineWidth_);
  saveSettings.setValue("vertexWidth", vertexWidth_);
  saveSettings.setValue("vertexType", vertexType_);

  saveSettings.setValue("colorLine.x", colorLine_.x());
  saveSettings.setValue("colorLine.y", colorLine_.y());
  saveSettings.setValue("colorLine.z", colorLine_.z());
  saveSettings.setValue("colorLine.w", colorLine_.w());

  saveSettings.setValue("colorBG.x", colorBG_.x());
  saveSettings.setValue("colorBG.y", colorBG_.y());
  saveSettings.setValue("colorBG.z", colorBG_.z());
  saveSettings.setValue("colorBG.w", colorBG_.w());

  saveSettings.setValue("colorVertex.x", colorVertex_.x());
  saveSettings.setValue("colorVertex.y", colorVertex_.y());
  saveSettings.setValue("colorVertex.z", colorVertex_.z());
  saveSettings.setValue("colorVertex.w", colorVertex_.w());

  saveSettings.setValue("objectDisplayType", objectDisplayType_);

  saveSettings.setValue("LigthtPosition.x", ligthtPosition_.x());
  saveSettings.setValue("LigthtPosition.y", ligthtPosition_.y());
  saveSettings.setValue("LigthtPosition.z", ligthtPosition_.z());
  saveSettings.setValue("LigthtPosition.w", ligthtPosition_.w());

  saveSettings.setValue("ligthtColor.x", ligthtColor_.x());
  saveSettings.setValue("ligthtColor.y", ligthtColor_.y());
  saveSettings.setValue("ligthtColor.z", ligthtColor_.z());
  saveSettings.setValue("ligthtColor.w", ligthtColor_.w());

  saveSettings.setValue("lightPower", lightPower_);

  saveSettings.setValue("objectDisplayType", objectDisplayType_);
  saveSettings.setValue("modelFilltype_", modelFilltype_);
}

void Settings::LoadFromFile() {
  QSettings loadSettings(filesettings, QSettings::IniFormat);
  setLineType(loadSettings.value("lineType", false).toBool());
  setProjectionType(loadSettings.value("projectionType", false).toBool());
  setLineWidth(loadSettings.value("line_width", 2).toInt());
  setVertexWidth(loadSettings.value("vertexWidth", 10).toInt());
  setVertexType(loadSettings.value("vertexType", 0).toInt());

  setColorLine(loadSettings.value("colorLine.x", 0).toFloat(),
               loadSettings.value("colorLine.y", 0.6).toFloat(),
               loadSettings.value("colorLine.z", 0).toFloat(),
               loadSettings.value("colorLine.w", 1).toFloat());

  setColorBG(loadSettings.value("colorBG.x", 0.2).toFloat(),
             loadSettings.value("colorBG.y", 0).toFloat(),
             loadSettings.value("colorBG.z", 0).toFloat(),
             loadSettings.value("colorBG.w", 1).toFloat());

  setColorVertex(loadSettings.value("colorVertex.x", 1).toFloat(),
                 loadSettings.value("colorVertex.y", 1).toFloat(),
                 loadSettings.value("colorVertex.z", 1).toFloat(),
                 loadSettings.value("colorVertex.w", 1).toFloat());

  setObjectDisplayType(loadSettings.value("objectDisplayType", 1).toInt());
  setModelFilltype(loadSettings.value("modelFilltype_", 0).toInt());

  setObjectDisplayType(loadSettings.value("objectDisplayType", 0).toInt());

  setLigthtPosition(loadSettings.value("LigthtPosition.x", 0.0).toFloat(),
                    loadSettings.value("LigthtPosition.y", 0.0).toFloat(),
                    loadSettings.value("LigthtPosition.z", 0.0).toFloat(),
                    loadSettings.value("LigthtPosition.w", 1).toFloat());
  setLigthtColor(loadSettings.value("ligthtColor.x", 1.0).toFloat(),
                 loadSettings.value("ligthtColor.y", 1.0).toFloat(),
                 loadSettings.value("ligthtColor.z", 1.0).toFloat(),
                 loadSettings.value("ligthtColor.w", 1).toFloat());
  setLightPower(loadSettings.value("lightPower", 90.0).toFloat());
}
}  // namespace s21
