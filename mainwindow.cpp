#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "linearinterpolation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_browse_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(
                this, "Select a file",
                "D:\Cources\Computer Vision\image_set"
//                QDir::currentPath()
                ,ui->cb_mosaic->isChecked()? "Images (*.jpg);;All Files (*)" :"Images (*.bmp);;All Files (*)" );
    if (fileName!="") {
        LinearInterpolation linear ;
        linear.SetPicture(fileName) ;
    }

}
