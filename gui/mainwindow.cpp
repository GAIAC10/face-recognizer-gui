#include "gui/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    face_cascade_ = new QAction("选择训练模型", this);
    this->connect(face_cascade_, SIGNAL(triggered()), SLOT(change_face_cascade()));

    // 将face_cascade_放在"文件"下
    cascade_file_menu = this->menuBar()->addMenu(tr("文件"));
    cascade_file_menu->addAction(face_cascade_);

    DisplayWidget* display = new DisplayWidget(this);
    display->connect(this, SIGNAL(face_cascade_filename_signal(QString)),SLOT(change_face_cascade_filename(QString)));
    // 设置主窗口
    setCentralWidget(display);
}

void MainWindow::change_face_cascade()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("HaarCascade Filename"));
    emit face_cascade_filename_signal(filename);
}

MainWindow::~MainWindow()
{
}

