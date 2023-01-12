#ifndef VIEW_H
#define VIEW_H

#include <QColorDialog>
#include <QDate>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QTimer>

#include "../Controller/controller.h"
#include "../settings.h"
#include "adapter.h"
#include "affine.h"
#include "glwidget.h"
#include "qgifimage.h"

#define ORGANIZATION_NAME "MS13"
#define ORGANIZATION_DOMAIN "www.s21.ru"
#define APPLICATION_NAME "3DViewer2.0"
#define SETTINGS_TRAY "settings/tray"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_pushButton_OpenFile_clicked();
  void on_comboBox_ProType_currentIndexChanged(int index);
  void on_spinBox_LineWidth_valueChanged(int arg1);
  void on_comboBox_LineType_currentIndexChanged(int index);
  void on_comboBox_VertexType_currentIndexChanged(int index);
  void on_spinBox_VertexWidth_valueChanged(int arg1);
  void on_pushButton_setColor_clicked();
  void on_pushButton_setColorBG_clicked();
  void on_pushButton_setColorVertex_clicked();
  void on_pushButton_defaultSettings_clicked();
  void on_pushButton_resetTransform_clicked();
  void on_pushButton_SAVE_clicked();
  void on_pushButton_LOAD_clicked();

  void on_pushButton_rotatePlusX_clicked();
  void on_pushButton_rotateMinusX_clicked();
  void on_pushButton_rotateMinusY_clicked();
  void on_pushButton_rotatePlusY_clicked();
  void on_pushButton_rotateMinusZ_clicked();
  void on_pushButton_rotatePlusZ_clicked();
  void on_pushButton_MoveMinusX_clicked();
  void on_pushButton_MovePlusX_clicked();
  void on_pushButton_MoveMinusY_clicked();
  void on_pushButton_MovePlusY_clicked();
  void on_pushButton_MoveMinusZ_clicked();
  void on_pushButton_MovePlusZ_clicked();
  void on_pushButton_scalePlus_clicked();
  void on_pushButton_scaleMinus_clicked();

  void on_pushButton_ScreenSave_clicked();
  void on_pushButton_record_clicked();
  void on_pushButton_saveGIF_clicked();

  void on_comboBox_objectDisplayType_currentIndexChanged(int index);

  void on_pushButton_ApplyLightPos_clicked();
  void on_pushButton_LightPower_clicked();
  void on_horizontalSlider_LightPower_sliderMoved(int position);

  void on_pushButton_LightColor_clicked();
  void on_pushButton_offTexture_clicked();
  void on_pushButton_applyTexture_clicked();

  void on_pushButton_UV_Map_clicked();

 private:
  Ui::View *ui;
  s21::Controller controller_;
  s21::Settings &settings_ = s21::Settings::getInstance();
  int gifFrameCounter_ = 0;

  QString getGifName();
  void screenSave(QString path);
  void checkRecordButton();
  void statusBarOutput(QString filePath);
  QString checkCurrentPath(int gifFrameNumber);

  QString textureFileName_;
};
#endif  // VIEW_H
