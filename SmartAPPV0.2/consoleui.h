#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <QWidget>
#include "movewidget.h"
#include "selfwidget.h"
#include "threewidget.h"
#include "tcpclient.h"
#include "controlModule.h"
#include <QHBoxLayout>
#include "def_const.h"
#include "mythread.h"
#define CONSOLESIZE QSize(800,600)
extern QString userToken;
namespace Ui {
class consoleUI;
}

class consoleUI : public QWidget
{
    Q_OBJECT

public:
    explicit consoleUI(controlModule *wh_control,QWidget *parent = 0);
    ~consoleUI();
    void paintBackground(QPixmap *pixmap);
protected slots:
    void ctlDataSend(QWidget*);
    void ctlDataRecved(uint8_t taskID,QJsonObject json);
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    Ui::consoleUI *ui;
    moveWidget * fanwidget;
    selfWidget * doorwidget;
    selfWidget * led1widget;
    selfWidget * led2widget;
    bool doorFlag,fanFlag,led1Flag,led2Flag;
    threeWidget *threewidget;
    QHBoxLayout  *threeLayout;
    controlModule *wh_control;
    myThread *thr;
    QPixmap *image;
    QPoint* dragPos;

};

#endif // CONSOLEUI_H
