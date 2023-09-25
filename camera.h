#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <QObject>
#include <QScopedPointer>
#include <QTimerEvent>
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QBasicTimer>
#include <QDebug>

class Camera : public QObject
{
    Q_OBJECT
    // 智能指针QScopedPointer
    // QScopedPointer<class名> 对象(new class名);
    // 对象.reset(new 类型名(reset的值));
    QScopedPointer<cv::VideoCapture> videoCapture_;
    QBasicTimer timer_;
    bool run_;
    bool usingVideoCamera_;
    int cameraIndex_;
    cv::String videoFileName_;

public:
    Camera(int camera_index=0, QObject* parent=0) : QObject(parent)
    {
        cameraIndex_ = camera_index;
        usingVideoCamera_ = true;
    }

    ~Camera();
    QImage convertToQImage( cv::Mat frame );

public slots:
    void runSlot();
    void cameraIndexSlot(int index);
    void videoFileNameSlot(QString fileName);
    void usingVideoCameraSlot(bool value);
    void stopped();

signals:
    void started();
    void matReady(const cv::Mat &);

private:
    // 虚函数,需要重写
    void timerEvent(QTimerEvent * ev);
};
