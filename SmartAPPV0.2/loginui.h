#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QHBoxLayout>
#include "login.h"
#include "controlModule.h"
#include "def_const.h"
#include <QPainter>
#include <QtGui>
extern QString userToken;

namespace Ui {
class loginUI;
}

extern QString userToken;

class loginUI : public QWidget
{
    Q_OBJECT

public:
    explicit loginUI(controlModule *wh_control,QWidget *parent = 0);
    ~loginUI();
public slots:
    void loginDataSend();
    void loginDataRecved(uint8_t taskID,QJsonObject json);
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    Ui::loginUI *ui;
    QHBoxLayout  *loginLayout;
    login *loginwidget;
    controlModule *wh_control;
    QString backgroundPic;
    QImage *backgroundPixmap;
    QPoint* dragPos;
};

#endif // LOGINUI_H
