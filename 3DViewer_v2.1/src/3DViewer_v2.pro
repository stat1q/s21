QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/modellistener.cpp \
    Model/parser.cpp \
    Model/vertex.cpp \
    Model/texture.cpp \
    Model/normal.cpp \
    Controller/controller.cpp \
    View/vertexesdatas.cpp \
    View/viewupdatelistener.cpp \
    settings.cpp \
    View/adapter.cpp \
    View/affine.cpp \
    View/glwidget.cpp \
    View/main.cpp \
    View/view.cpp

HEADERS += \
    Model/modellistener.h \
    Model/parser.h \
    Model/vertex.h \
    Model/texture.h \
    Model/normal.h \
    Controller/controller.h \
    View/vertexesdatas.h \
    View/viewupdatelistener.h \
    settings.h \
    View/adapter.h \
    View/affine.h \
    View/glwidget.h \
    View/view.h
    include(qtgifimage/src/gifimage/qtgifimage.pri)

FORMS += \
    View/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    View/fshader.fsh \
    View/vshader.vsh

DEFINES += SRCDIR=\\\"$$PWD/\\\" \

RESOURCES += \
    View/shaders.qrc

win32-g* {
LIBS += -lopengl32
}

win32-msvc* {
LIBS += lopengl32.lib
}
