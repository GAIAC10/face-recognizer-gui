QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = opencv
TEMPLATE = app
DESTDIR = $$PWD

SOURCES += main.cpp \
    gui/mainwindow.cpp \
    camera.cpp \
    gui/displaywidget.cpp \
    faceDetector.cpp \
    gui/imageviewer.cpp

HEADERS += gui/mainwindow.h \
    camera.h \
    gui/displaywidget.h \
    faceDetector.h \
    gui/imageviewer.h

# opencv(按照自己的路径)
# 添加opencv见https://blog.csdn.net/weixin_43763292/article/details/112975207
INCLUDEPATH += F:\Project_C++\OpenCV-4.5.4\opencv\opencv-build\install\include
LIBS += F:\Project_C++\OpenCV-4.5.4\opencv\opencv-build\lib\libopencv_*.a
