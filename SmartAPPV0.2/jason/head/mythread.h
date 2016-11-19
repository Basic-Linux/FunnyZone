#ifndef THREAD_H
#define THREAD_H
#include <QWidget>
#include "movewidget.h"
#include "selfwidget.h"
#include "threewidget.h"
#include "tcpclient.h"
#include "controlModule.h"
#include <QHBoxLayout>
#include "def_const.h"
#include <QThread>
#include <QTimer>
extern QString userToken;
class myThread : public QThread
{
    Q_OBJECT

public:
    explicit myThread(controlModule *wh_control,QObject * parent = 0);
    ~myThread();
    void setP_ControlModule(controlModule *wh_control);
protected:
    void run() Q_DECL_OVERRIDE;
private:
    controlModule *wh_control;
    QTimer *clock;
};
#endif
