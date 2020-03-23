#ifndef QIMAGESHOWWIDGET_H
#define QIMAGESHOWWIDGET_H

#include <QWidget>

class QImageShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QImageShowWidget(QWidget *parent = nullptr);
    ~QImageShowWidget();

    bool LoadImage(const char* imagePath);
signals:

public slots:

protected:
    void paintEngine(QPaintEngine *);
    void Release();

private:
    uchar* winBuf;
    int winWidth;
    int winHeight;
    int winBandNum;

};

#endif // QIMAGESHOWWIDGET_H
