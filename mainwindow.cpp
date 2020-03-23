#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include<iostream>
#include<QFile>
#include<QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString file= QFileDialog::getOpenFileName(this,QString("选择第一幅图片"),QString("/"),QString("*"));
    QImage img(file);
    if(img.isNull())
    {
        fprintf(stderr,"Can not load image %s\n",file);
    }
    ui->label_12->setScaledContents(true);
    QSize qs=ui->label_12->rect().size();
    ui->label_12->setPixmap(QPixmap::fromImage(img).scaled(qs));

    QString file2= QFileDialog::getOpenFileName(this,QString("选择第二幅图片"),QString("/"),QString("*"));
    QImage img2(file2);
    if(img.isNull())
    {
        fprintf(stderr,"Can not load image %s\n",file);
    }

    ui->label_13->setScaledContents(true);
    QSize qs2 = ui->label_13->rect().size();
    ui->label_13->setPixmap(QPixmap::fromImage(img2).scaled(qs2));

}
