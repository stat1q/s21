#include "view.h"

#include "ui_view.h"

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  s21::Adapter *adapter = new s21::Adapter;
  controller_.getModel().setUpdater(adapter);
  ui->setupUi(this);
  this->setWindowTitle(APPLICATION_NAME);
  adapter->setUpdater(ui->OGLWidget);
  on_pushButton_LOAD_clicked();
  ui->OGLWidget->getAffine().set_move_z(-3);
}

View::~View() { delete ui; }

void View::on_pushButton_OpenFile_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Open File"), SRCDIR "obj_files", "All files (*.obj)");
  if (!filePath.isEmpty()) {
    on_pushButton_offTexture_clicked();
    controller_.callParser(filePath.toStdString());
  }
  statusBarOutput(filePath);
  controller_.clearModel();
};

void View::statusBarOutput(QString filePath) {
  statusBar()->showMessage(
      "Количество вершин: " + QString::number(controller_.getVertexCount()) +
      ".   Количество полигонов: " +
      QString::number(controller_.getFlatCount()) +
      ".   Путь к файлу:  " + filePath);
}

void View::on_pushButton_rotatePlusX_clicked() {
  ui->OGLWidget->getAffine().set_rotation_x(ui->doubleSpinBox_setX->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_rotateMinusX_clicked() {
  ui->OGLWidget->getAffine().set_rotation_x(-1 *
                                            ui->doubleSpinBox_setX->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_rotateMinusY_clicked() {
  ui->OGLWidget->getAffine().set_rotation_y(-1 *
                                            ui->doubleSpinBox_setY->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_rotatePlusY_clicked() {
  ui->OGLWidget->getAffine().set_rotation_y(ui->doubleSpinBox_setY->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_rotateMinusZ_clicked() {
  ui->OGLWidget->getAffine().set_rotation_z(-1 *
                                            ui->doubleSpinBox_setZ->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_rotatePlusZ_clicked() {
  ui->OGLWidget->getAffine().set_rotation_z(ui->doubleSpinBox_setZ->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_MoveMinusX_clicked() {
  ui->OGLWidget->getAffine().set_move_x(-1 * ui->doubleSpinBox_MoveX->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_MovePlusX_clicked() {
  ui->OGLWidget->getAffine().set_move_x(ui->doubleSpinBox_MoveX->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_MoveMinusY_clicked() {
  ui->OGLWidget->getAffine().set_move_y(-1 * ui->doubleSpinBox_MoveY->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_MovePlusY_clicked() {
  ui->OGLWidget->getAffine().set_move_y(ui->doubleSpinBox_MoveY->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_MoveMinusZ_clicked() {
  ui->OGLWidget->getAffine().set_move_z(-1 * ui->doubleSpinBox_MoveZ->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_MovePlusZ_clicked() {
  ui->OGLWidget->getAffine().set_move_z(ui->doubleSpinBox_MoveZ->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_scalePlus_clicked() {
  ui->OGLWidget->getAffine().set_scalePlus(ui->doubleSpinBox_Scale->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_scaleMinus_clicked() {
  ui->OGLWidget->getAffine().set_scaleMinus(ui->doubleSpinBox_Scale->value());
  ui->OGLWidget->update();
  checkRecordButton();
}

void View::on_pushButton_resetTransform_clicked() {
  ui->OGLWidget->getAffine().set_resetTransform();
  ui->OGLWidget->update();
}

void View::on_comboBox_ProType_currentIndexChanged(int index) {
  settings_.setProjectionType(index);
  ui->OGLWidget->projectionSelect();
  if (index == 1) {
    ui->pushButton_MoveMinusZ->setEnabled(false);
    ui->pushButton_MovePlusZ->setEnabled(false);
    ui->doubleSpinBox_MoveZ->setEnabled(false);
  } else {
    ui->pushButton_MoveMinusZ->setEnabled(true);
    ui->pushButton_MovePlusZ->setEnabled(true);
    ui->doubleSpinBox_MoveZ->setEnabled(true);
  }
}

void View::on_spinBox_LineWidth_valueChanged(int arg1) {
  settings_.setLineWidth(arg1);
  ui->OGLWidget->update();
}

void View::on_comboBox_LineType_currentIndexChanged(int index) {
  settings_.setLineType(index);
  ui->OGLWidget->update();
}

void View::on_comboBox_objectDisplayType_currentIndexChanged(int index) {
  if (!index) {
    ui->pushButton_applyTexture->setEnabled(false);
    ui->pushButton_offTexture->setEnabled(false);
  } else {
    ui->pushButton_applyTexture->setEnabled(true);
    ui->pushButton_offTexture->setEnabled(true);
  }
  settings_.setObjectDisplayType(index);
  ui->OGLWidget->update();
}

void View::on_comboBox_VertexType_currentIndexChanged(int index) {
  if (ui->comboBox_VertexType->currentIndex() != 0) {
    ui->spinBox_VertexWidth->setEnabled(true);
    ui->label_Width->setEnabled(true);
    ui->label_colorVertex->setEnabled(true);
    ui->widget_colorVretex->setEnabled(true);
    ui->pushButton_setColorVertex->setEnabled(true);

  } else {
    ui->spinBox_VertexWidth->setEnabled(false);
    ui->label_Width->setEnabled(false);
    ui->label_colorVertex->setEnabled(false);
    ui->widget_colorVretex->setEnabled(false);
    ui->pushButton_setColorVertex->setEnabled(false);
  }
  settings_.setVertexType(index);
  ui->OGLWidget->update();
}

void View::on_spinBox_VertexWidth_valueChanged(int arg1) {
  settings_.setVertexWidth(arg1);
  ui->OGLWidget->update();
}

void View::on_pushButton_setColor_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->widget_colorLine->setStyleSheet(
        QString("background-color: %1;").arg(color.name(QColor::HexArgb)));
    settings_.setColorLine(color.redF(), color.greenF(), color.blueF(),
                           color.alphaF());
  }
}

void View::on_pushButton_setColorBG_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->widget_BG->setStyleSheet(
        QString("background-color: %1;").arg(color.name(QColor::HexArgb)));
    settings_.setColorBG(color.redF(), color.greenF(), color.blueF(),
                         color.alphaF());
  }
}

void View::on_pushButton_setColorVertex_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->widget_colorVretex->setStyleSheet(
        QString("background-color: %1;").arg(color.name(QColor::HexArgb)));
    settings_.setColorVertex(color.redF(), color.greenF(), color.blueF(),
                             color.alphaF());
  }
}

void View::on_pushButton_defaultSettings_clicked() {
  if (QFile::exists(SRCDIR "etc/config.ini")) {
    QFile::remove(SRCDIR "etc/config.ini");
  }
  on_pushButton_LOAD_clicked();
}

void View::on_pushButton_SAVE_clicked() { settings_.SaveInFile(); }

void View::on_pushButton_LOAD_clicked() {
  settings_.LoadFromFile();
  ui->comboBox_LineType->setCurrentIndex(settings_.getLineType());
  ui->comboBox_ProType->setCurrentIndex(settings_.getProjectionType());
  ui->spinBox_LineWidth->setValue(settings_.getLineWidth());
  ui->OGLWidget->projectionSelect();
  ui->spinBox_VertexWidth->setValue(settings_.getVertexWidth());
  ui->comboBox_VertexType->setCurrentIndex(settings_.getVertexType());

  QColor coloLine = QColor(
      settings_.getColorLine().x() * 255, settings_.getColorLine().y() * 255,
      settings_.getColorLine().z() * 255, settings_.getColorLine().w() * 255);
  ui->widget_colorLine->setStyleSheet(
      QString("background-color: %1;").arg(coloLine.name(QColor::HexArgb)));

  QColor colorBG = QColor(
      settings_.getColorBG().x() * 255, settings_.getColorBG().y() * 255,
      settings_.getColorBG().z() * 255, settings_.getColorBG().w() * 255);
  ui->widget_BG->setStyleSheet(
      QString("background-color: %1;").arg(colorBG.name(QColor::HexArgb)));

  QColor colorVertex = QColor(settings_.getColorVertex().x() * 255,
                              settings_.getColorVertex().y() * 255,
                              settings_.getColorVertex().z() * 255,
                              settings_.getColorVertex().w() * 255);
  ui->widget_colorVretex->setStyleSheet(
      QString("background-color: %1;").arg(colorVertex.name(QColor::HexArgb)));

  QColor ColorLightning = QColor(settings_.getLigthtColor().x() * 255,
                                 settings_.getLigthtColor().y() * 255,
                                 settings_.getLigthtColor().z() * 255,
                                 settings_.getLigthtColor().w() * 255);
  ui->widget_LightColor->setStyleSheet(
      QString("background-color: %1;")
          .arg(ColorLightning.name(QColor::HexArgb)));

  ui->comboBox_objectDisplayType->setCurrentIndex(
      settings_.getObjectDisplayType());
}

////  Part 3. Дополнительно. Record ////

QString View::getGifName() {
  QString filename = checkCurrentPath(gifFrameCounter_);
  gifFrameCounter_++;
  return filename;
}

void View::on_pushButton_ScreenSave_clicked() {
  QString fileType;
  ui->comboBox_FileType->currentIndex() == 0 ? fileType = "bmp"
                                             : fileType = "jpg";
  QString fileName = QDate::currentDate().toString() + " " +
                     QTime::currentTime().toString() + "." + fileType;
  QString path = QFileDialog::getSaveFileName(this, tr("Save file"),
                                              SRCDIR "screenshots/" + fileName,
                                              "Images (*" + fileType + ")");
  screenSave(path);
}

void View::screenSave(QString path) {
  QImage screen = ui->OGLWidget->grabFramebuffer();
  if (ui->pushButton_record->text() == "Record") {
    screen.save(path, nullptr, -1);
  } else {
    QImage scaledScreen =
        screen.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    scaledScreen.save(path, nullptr, 0);
  }
}

void View::checkRecordButton() {
  if (ui->pushButton_record->text() == "Stop") {
    screenSave(getGifName());
  }
}

void View::on_pushButton_record_clicked() {
  QDir dir;
  if (QDir::currentPath() == QDir::rootPath()) {
    dir.setPath(SRCDIR "3DViewer/3DViewer_v2.app/Contents/MacOS/gif");
  } else {
    dir.setPath(QDir::currentPath() + "/gif");
  }
  if (ui->pushButton_record->text() == "Record") {
    qDebug() << "Record";
    ui->pushButton_record->setText("Stop");
    if (!dir.exists()) {
      dir.mkpath(".");
    }
    if (ui->checkBox_autoRecording->isChecked()) {
      for (int i = 0; i < 50; i++) {
        on_pushButton_rotatePlusY_clicked();
      }
      on_pushButton_record_clicked();
    } else {
      screenSave(getGifName());
    }
  } else if (ui->pushButton_record->text() == "Stop") {
    qDebug() << "Stop";
    ui->pushButton_record->setText("Delete");
    ui->pushButton_saveGIF->setEnabled(true);
  } else if (ui->pushButton_record->text() == "Delete") {
    qDebug() << "Delete";
    dir.removeRecursively();
    ui->pushButton_record->setText("Record");
    ui->pushButton_saveGIF->setEnabled(false);
    gifFrameCounter_ = 0;
  }
}

void View::on_pushButton_saveGIF_clicked() {
  qDebug() << "Save";
  QString gifName = "gifImage";
  QString filename = QFileDialog::getSaveFileName(
      this, "Выберите место сохранения gif", SRCDIR "screenshots/" + gifName,
      "Gif(*.gif) ;; All files (*.*)");
  if (!filename.isNull()) {
    ui->pushButton_record->setText("Record");
    ui->pushButton_saveGIF->setEnabled(false);
    qDebug() << filename;
    QGifImage gif(QSize(640, 480));
    gif.setDefaultDelay(100);
    for (int i = 0; i < gifFrameCounter_; ++i) {
      QString filenameimage = checkCurrentPath(i);
      QImage image(filenameimage, "BMP");
      gif.addFrame(image, 100);
    }
    gif.save(filename);
    QDir dir(QDir::currentPath() + "/gif");
    dir.removeRecursively();
    gifFrameCounter_ = 0;
  }
}

QString View::checkCurrentPath(int gifFrameNumber) {
  QString filename;
  if (QDir::currentPath() == QDir::rootPath()) {
    filename = SRCDIR "3DViewer/3DViewer_v2.app/Contents/MacOS/gif/gif_frame_" +
               QString::number(gifFrameNumber) + ".bmp";
  } else {
    filename = QDir::currentPath() + "/gif/gif_frame_" +
               QString::number(gifFrameNumber) + ".bmp";
  }
  return filename;
}

////  Part 4. Дополнительно. Текстурирование ////

void View::on_pushButton_applyTexture_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Open File"), SRCDIR "obj_files/textures/", "All files (*.bmp)");
  if (!filePath.isEmpty()) {
    textureFileName_ = filePath;
    ui->OGLWidget->applyTexture(filePath);
  }
}

void View::on_pushButton_ApplyLightPos_clicked() {
  settings_.setLigthtPosition(ui->doubleSpinBox_LightPosX->value(),
                              ui->doubleSpinBox_LightPosY->value(),
                              ui->doubleSpinBox_LightPosZ->value(), 1.0);
}

void View::on_pushButton_LightPower_clicked() {
  settings_.setLightPower(999999);
}

void View::on_horizontalSlider_LightPower_sliderMoved(int position) {
  settings_.setLightPower(200 - position);
}

void View::on_pushButton_LightColor_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->widget_LightColor->setStyleSheet(
        QString("background-color: %1;").arg(color.name(QColor::HexArgb)));
    settings_.setLigthtColor(color.redF(), color.greenF(), color.blueF(),
                             color.alphaF());
  }
}

void View::on_pushButton_offTexture_clicked() { ui->OGLWidget->offTexture(); }

void View::on_pushButton_UV_Map_clicked() {
  ui->OGLWidget->paintMap(textureFileName_);
}
