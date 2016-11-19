#include "controlModule.h"
#include "def_const.h"

controlModule::controlModule(QObject *parent) : QObject(parent),
    wh_socket(new tcpClient("192.168.1.111",8888))
{
    wh_socket->connectSocket();

    connect(wh_socket->tcpSocket,SIGNAL(readyRead()),this,SLOT(socketdataRecved()));
}
controlModule::~controlModule()
{

}

tcpClient * controlModule::getTcpClient()
{
    return this->wh_socket;
}

void controlModule::socketdataSend(uint8_t taskID,QJsonObject &json_object)
{

    QByteArray byteArray;
    short len;
    byteArray.append(APP_TO_A9);
    byteArray.append(taskID);
    len = QString(QJsonDocument(json_object).toJson()).length();
    //For BigEndian PLATFORM TO LittleEndian PLATFORM
    byteArray.append((char *)&len + 1 ,sizeof(char));
    byteArray.append((char *)&len,sizeof(char));
    byteArray.append(QString(QJsonDocument(json_object).toJson()));
    wh_socket->dataSend(byteArray);

    DBUG_OUT;
}
void controlModule::socketdataRecved()
{
    QByteArray byteArray = wh_socket->dataReceived();
    if(byteArray.at(MSGNUMSITE) == CTLHUM || byteArray.at(MSGNUMSITE) == CTLLUX || byteArray.at(MSGNUMSITE)  == CTLTEMP)
    {
        byteArray.truncate(byteArray.at(MSGLENSITE1) + 4);
    }
    QJsonObject json_object;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(( byteArray.data() + MSGJSONSITE ),&json_error);
    json_object = parse_doucment.object();
    if(byteArray.at(MSGTYPESITE) == A9_TO_APP)
    {

        emit sigDataRecved(byteArray.at(MSGNUMSITE),json_object);
    }
    else
    {
        qDebug() << "byte   " << byteArray.at(MSGTYPESITE);
        qDebug("recv format is error");
    }
    DBUG_OUT;
}
