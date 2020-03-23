#include "qimageshowwidget.h"
#include <QPainter>
#include <QDebug>
#include<iostream>


using namespace std;
QImageShowWidget::QImageShowWidget(QWidget *parent) : QWidget(parent)
{

    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);


    winBuf = nullptr;
    winWidth = rect().width();
    winHeight = rect().height();
    winBandNum = 3;
}

QImageShowWidget::~QImageShowWidget()
{
    if(winBuf)
    {
        delete[] winBuf;
        winBuf = nullptr;
    }
}

bool QImageShowWidget::LoadImage(const char* imagePath)
{
    QImage img(imagePath);
    if(img.isNull())
    {
        fprintf(stderr,"Can not load image %s\n",imagePath);
        return false;
    }

 //   Release();

    winWidth = rect().width();
    winHeight = rect().height();
}
