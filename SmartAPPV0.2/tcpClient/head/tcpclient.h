#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QTextStream>
#include <QTextCodec>
#include <QMessageBox>
class tcpClient : public QObject
{
    Q_OBJECT

public:
    tcpClient(QString ip,int port,QObject *parent = 0);
    ~tcpClient();
    void creatSocket(QString ip,int port);
    void connectSocket();
    QTcpSocket *tcpSocket;
public slots:
    void dataSend(QByteArray byteArray);
    QByteArray dataReceived();
    void stateChanged();
private:
    int port;
    QHostAddress *serverIP;
    bool connected;

};

#endif // TCPCLIENT_H
