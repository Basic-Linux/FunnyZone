#include "mythread.h"

myThread::myThread(controlModule *wh_control,QObject *parent)
    :QThread(parent)
{
    this->wh_control = wh_control;
}
myThread::~myThread()
{

}
void myThread::setP_ControlModule(controlModule *wh_control)
{
    this->wh_control = wh_control;
}
void myThread::run()
{
    QJsonObject json_object;
    json_object.insert(J_userName,"111");
    json_object.insert(J_password,"111");
    json_object.insert(J_userToken,userToken);
    json_object.insert(J_deviceNumber,0);
    while(1)
    {
        wh_control->socketdataSend(CTLTEMP,json_object);
        QThread::sleep(1);
        wh_control->socketdataSend(CTLHUM,json_object);
        QThread::sleep(1);
        wh_control->socketdataSend(CTLLUX,json_object);
        QThread::sleep(1);
    }
}
