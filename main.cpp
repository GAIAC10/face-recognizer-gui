#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda_types.hpp>
#include <opencv2/core/cuda.inl.hpp>
#include <QDebug>
#include "gui/mainwindow.h"

// 一定要使用绝对路径，其他可以回报错
//Mat image=imread("C:\\Users\\hp\\Pictures\\map\\01.jpg",1);

// 因为opencv不是继承的类，所以要注册新类
// QVariant::fromValue()/QVariant::setValue()
// QVariant::canConvert()
// QVariant::value()
Q_DECLARE_METATYPE(cv::Mat)

int main( int argc, char* argv[] )
{
    // 传递参数自定义,跨线程,需要qRegisterMetaType
    qRegisterMetaType<cv::Mat>();
	QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle(QStringLiteral("人脸检测系统"));
    window.show();
	return app.exec();
}
