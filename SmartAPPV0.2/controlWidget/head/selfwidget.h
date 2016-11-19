#ifndef SELFWIDGET_H
#define SELFWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QtGui>
class selfWidget : public QWidget
{
    Q_OBJECT
public:
    explicit selfWidget(QString file_on,QString file_off,QSize size,QWidget *parent);
    ~selfWidget();
    void initSelfWidget(QString file_on,QString file_off,QSize size);
    bool stateFlag;
signals:
    void clicked(QWidget *);
public slots:
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
private:
    QPixmap* backgroundPixmap_on;
    QPixmap* backgroundPixmap_off;

};

#endif // SELFWIDGET_H
