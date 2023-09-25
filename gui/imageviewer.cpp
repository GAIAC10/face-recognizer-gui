#include "gui/imageviewer.h"

void ImageViewer::set_image(const QImage &img)
{
    // 有帧
    if (!image_.isNull())
    {
        qDebug() << "Viewer dropped frame!";
    }
    image_ = img;
    if (image_.size() != size())
        // 设置图片大小
        setFixedSize(image_.size());
        update();
}
