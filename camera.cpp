#include "camera.h"

Camera::~Camera()
{
}

void Camera::runSlot()
{
    // TODO: clean up. Would be nice not to have nested `if` statements

    // 类型为QScopedPointer<cv::VideoCapture> or bool
    if (!videoCapture_ or !usingVideoCamera_)
    {
        // 勾选按钮,需要选择另一个摄像头
        // 没有勾选按钮,需要选择文件
        if (usingVideoCamera_)
            videoCapture_.reset(new cv::VideoCapture(cameraIndex_));
        else
            videoCapture_.reset(new cv::VideoCapture(videoFileName_));
    }
    if (videoCapture_->isOpened())
    {
        timer_.start(0, this);
        emit started();
    }
}

void Camera::stopped()
{
    timer_.stop();
}

// 1.重写QTimer类中的timerEvent()方法(timer到时间就会调用重写的event)
// 2.创建QTimer类对象
//QTimer *timer = new QTimer(this);
//timer->start(500);
//connect(timer, &QTimer::timeout, [=](){
//    static int num = 1;
//    ui->label4->setText(QString::number(num++));
//});

// 重写timerEvent方法(此cpp只有一个timer)
void Camera::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() != timer_.timerId())
    {
        return;
    }
    cv::Mat frame;
    if (!videoCapture_->read(frame)) // Blocks until a new frame is ready
    {
        timer_.stop();
        return;
    }
    emit matReady(frame);
}

void Camera::usingVideoCameraSlot(bool value)
{
    usingVideoCamera_ = value;
}

void Camera::cameraIndexSlot(int index)
{
    cameraIndex_ = index;
}

void Camera::videoFileNameSlot(QString fileName)
{
    videoFileName_ = fileName.toStdString().c_str();
}
