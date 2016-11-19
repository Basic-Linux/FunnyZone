#include "selfwidget.h"

selfWidget::selfWidget(QString file_on,QString file_off,QSize size,QWidget *parent) : QWidget(parent)
{
    initSelfWidget(file_on,file_off,size);
}
selfWidget::~selfWidget()
{
    delete backgroundPixmap_on;
    delete backgroundPixmap_off;
}
void selfWidget::mousePressEvent(QMouseEvent * event)
{
    emit clicked(this);
}
void selfWidget::initSelfWidget(QString file_on,QString file_off,QSize size)
{
    stateFlag = false;
    backgroundPixmap_on = new QPixmap(file_on);
    *backgroundPixmap_on = backgroundPixmap_on->scaled(size);
    backgroundPixmap_off = new QPixmap(file_off);
    *backgroundPixmap_off = backgroundPixmap_off->scaled(size);
    this->resize(size);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);
}
void selfWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(stateFlag)
    {
        //qDebug("stateflag true");
        this->setMask(backgroundPixmap_on->mask());
        painter.drawPixmap(0,0,backgroundPixmap_on->width(),backgroundPixmap_on->height(),*backgroundPixmap_on);
    }
    else
    {
        //qDebug("stateflag false");
        this->setMask(backgroundPixmap_off->mask());
        painter.drawPixmap(0,0,backgroundPixmap_off->width(),backgroundPixmap_off->height(),*backgroundPixmap_off);
    }
}
