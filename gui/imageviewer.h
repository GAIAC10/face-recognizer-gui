#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDebug>

class ImageViewer : public QWidget
{
    Q_OBJECT
    QImage image_;

    // 当发生一下情况时会产生绘制事件并调用paintEvent()函数
    // update()函数自动调用
    void paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        // (目标矩形,源矩形,图片)
        p.drawImage(0, 0, image_);
        // 初始化
        image_ = QImage();
    }

public:
    explicit ImageViewer(QWidget *parent = 0) : QWidget(parent)
    {
        // 设置之后，qt不会将上次的屏幕擦除
        setAttribute(Qt::WA_OpaquePaintEvent);
    }

signals:

public slots:
    void set_image(const QImage & img);
};

#endif // IMAGEVIEWER_H
