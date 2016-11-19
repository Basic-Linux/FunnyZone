#include "movewidget.h"

//==========================================
moveWidget::moveWidget(QString file,QSize size,QWidget *parent)
    : QWidget(parent)
{
    initmoveWidget(file,size);
}

moveWidget::~moveWidget()
{
    delete backgroundPixmap;
    delete timer;
    delete dragPos;
}
void moveWidget::initmoveWidget(QString file,QSize size)
{
    this->resize(size);
    //设置透明背景
//    QPalette pl;
//    pl.setBrush(QPalette::Window,QBrush(QColor(255,0,0,255)));
//    this->setPalette(pl);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);
    //设置图片
    backgroundPixmap = new QPixmap(file);
    *backgroundPixmap = backgroundPixmap->scaled(this->size());
    //设置坐标
    dragPos = new QPoint();
    //设置定时器相关信息
    timer = new QTimer();
    roateFlag = false;
    rotate = 0;
    connect(timer,SIGNAL(timeout()),this,SLOT(roateWidget()),Qt::DirectConnection);
    timer->start(10);
}
void moveWidget::roateWidget()
{
    if(roateFlag)
    this->update();
}
void moveWidget::mousePressEvent(QMouseEvent * event)
{
    emit clicked(this);
}
void moveWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(roateFlag){
         rotate = (rotate + 1) % 360;
    }

    QPoint centrepoint = QPoint(backgroundPixmap->width() / 2,backgroundPixmap->height() / 2);
    painter.translate(centrepoint);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.rotate(rotate);
    //qDebug() << "rotate = "<< rotate;
    painter.drawPixmap(- backgroundPixmap->width() / 2, - backgroundPixmap->height() / 2,backgroundPixmap->width()
                       ,backgroundPixmap->height(),*backgroundPixmap);
}

