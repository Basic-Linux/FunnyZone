#ifndef controlModule_H
#define controlModule_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "tcpclient.h"


class controlModule : public QObject
{
    Q_OBJECT
public:
    explicit controlModule(QObject *parent = 0);
    ~controlModule();
    tcpClient * getTcpClient();
signals:
    sigDataRecved(uint8_t taskID,QJsonObject json);//本信号 在socketdataRecved中发送
    //sigDataSend(uint8_t taskID,QJsonObject json); 应该在别处发送
public slots:
    void socketdataSend(uint8_t taskID,QJsonObject &json_object);
    void socketdataRecved();
private:
    tcpClient *wh_socket;
};

#endif // controlModule_H
