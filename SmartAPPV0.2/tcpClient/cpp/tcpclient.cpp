#include "tcpclient.h"
#include "def_const.h"
tcpClient::tcpClient(QString ip,int port,QObject *parent)
    : QObject(parent),
      connected(false)
{
    creatSocket(ip,port);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(stateChanged()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(stateChanged()));
}

tcpClient::~tcpClient()
{

}
void tcpClient::stateChanged()
{
    if(tcpSocket->isValid())
        connected = true;
    else
        connected = false;
}
void tcpClient::creatSocket(QString ip,int port)
{
    this->serverIP = new QHostAddress(ip);
    this->port = port;
    tcpSocket = new QTcpSocket(this);
    if(!tcpSocket)
    {
         QMessageBox::warning(0,tr("网络错误"),tr("new QTcpSocket() 错误"));
    }
    DBUG_OUT;
}
void tcpClient::connectSocket()
{
    tcpSocket->connectToHost(*serverIP, port,QIODevice::ReadWrite);
    DBUG_OUT;
}
void tcpClient::dataSend(QByteArray byteArray)
{
    int res;
    if(connected)
    {
        res = tcpSocket->write(byteArray);
        if(res == -1)
        {

            qDebug() << "socket send err =" << tcpSocket->errorString();
        }
        tcpSocket->flush();
#ifdef DEBUG
    //For BigEndian PLATFORM TO LittleEndian PLATFORM
    qDebug("send msg = %x %x %x%x %s",byteArray.at(MSGTYPESITE)&0xff,byteArray.at(MSGNUMSITE),
           byteArray.at(MSGLENSITE0),byteArray.at(MSGLENSITE1),byteArray.data() + MSGJSONSITE);
#endif
    }
    else
    {
        QMessageBox::warning(0,tr("网络错误"),tr("链接中断请稍后再试"));
        connectSocket();
    }
    DBUG_OUT;
}
QByteArray tcpClient::dataReceived()
{
    QByteArray byteArray;
    while (tcpSocket->bytesAvailable() > 0 )
    {
        byteArray = tcpSocket->read(PACKETLEN);
#ifdef DEBUG
    qDebug("recv0 msg = %x %x %x%x %s",byteArray.at(MSGTYPESITE)&0xff,byteArray.at(MSGNUMSITE),
           byteArray.at(MSGLENSITE0),byteArray.at(MSGLENSITE1),byteArray.data() + MSGJSONSITE);
#endif
    }
    DBUG_OUT;
    return byteArray;
}

