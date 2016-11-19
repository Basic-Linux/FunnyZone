#ifndef MOVEWIDGET_H
#define MOVEWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QTimer>
#include <QPainter>
#include <QTimer>
#include <QDebug>

//============backgroundWidget=============
class moveWidget : public QWidget
{
    Q_OBJECT

public:
    moveWidget(QString file,QSize size,QWidget *parent = 0);
    ~moveWidget();
    void initmoveWidget(QString file,QSize size);
    bool roateFlag;
signals:
    void clicked(QWidget *);
protected slots:
    void roateWidget();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
private:
    //该图片最好为圆形
    QPixmap* backgroundPixmap;
    QTimer *timer;
    QPoint* dragPos;
    int rotate;
    const QString file = ":/fan_ico.png";

};



#endif // MOVEWIDGET_H
