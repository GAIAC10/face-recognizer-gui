#include "gui/displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
    QStringList cameraOptions;
    cameraOptions << "0" << "1";
    QComboBox* cameraComboBox = new QComboBox;
    cameraComboBox->addItems(cameraOptions);

    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    QPushButton *runButton = new QPushButton("开始人脸检测", this);
    QPushButton *fileSelector = new QPushButton("选择视频文件");
    horizontalLayout->addWidget(cameraComboBox);
    horizontalLayout->addWidget(fileSelector);
    horizontalLayout->addWidget(runButton);

    // 整体布局
    QVBoxLayout *layout = new QVBoxLayout;
    // 视频显示并画图窗口
    image_viewer_ = new ImageViewer(this);
    QRadioButton *sourceSelector = new QRadioButton("Stream from video camera", this);
    sourceSelector->setDown(true);

    // 视频窗口
    layout->addWidget(image_viewer_);
    layout->addLayout(horizontalLayout);
    layout->addWidget(sourceSelector);
    setLayout(layout);

    camera_ = new Camera();
    faceDector_ = new FaceDetector();

    //faceDector_->setProcessAll(false);

    // 开启人脸识别多线程
    faceDetectThread_.start();
    // 开启拍照多线程
    cameraThread_.start();

    camera_->moveToThread(&cameraThread_);
    faceDector_->moveToThread(&faceDetectThread_);

    // TODO: Add in slot to turn off camera_, or something
    image_viewer_->connect(faceDector_,SIGNAL(image_signal(QImage)), SLOT(set_image(QImage)));

    faceDector_->connect(camera_, SIGNAL(matReady(cv::Mat)), SLOT(processFrame(cv::Mat)));

    QObject::connect(runButton, SIGNAL(clicked()), camera_, SLOT(runSlot()));

    QObject::connect(cameraComboBox, SIGNAL(currentIndexChanged(int)), camera_, SLOT(cameraIndexSlot(int)));// 选择摄像头

    QObject::connect(fileSelector, SIGNAL(clicked()),this,	SLOT(openFileDialog()));// 选择文件,发送文件名信号到最后一个QObject::connect

    QObject::connect(sourceSelector, SIGNAL(toggled(bool)), camera_, SLOT(usingVideoCameraSlot(bool))); // 勾选按钮(默认勾选),设置usingVideoCamera_,用于if判断

    QObject::connect(this, SIGNAL(videoFileNameSignal(QString)), camera_, SLOT(videoFileNameSlot(QString)));// 设置videoFileName_,用于if判断

    faceDector_->connect(this, SIGNAL(facecascade_name_signal(QString)), SLOT(facecascade_filename(QString)));// 设置训练模型
}

DisplayWidget::~DisplayWidget()
{
    faceDector_->~FaceDetector();
    camera_->~Camera();
    faceDetectThread_.quit();
    cameraThread_.quit();
    faceDetectThread_.wait();
    cameraThread_.wait();
}

void DisplayWidget::change_face_cascade_filename(QString filename)
{
    emit facecascade_name_signal(filename);
}

void DisplayWidget::openFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Video"));
    emit videoFileNameSignal(filename);
}
