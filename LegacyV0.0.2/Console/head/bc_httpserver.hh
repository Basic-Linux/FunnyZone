#ifndef BC_HTTPSERVER_H
#define BC_HTTPSERVER_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QRegExp>
#include "qhttpAllHeadFile.h"

#define HTTPPORT 9090

class bc_HttpServer : public QObject
{
    Q_OBJECT

public:
    explicit bc_HttpServer(QObject *parent = 0);
    ~bc_HttpServer();

    void httpDeal(QHttpRequest *req, QHttpResponse *resp);

    void sendHttpMsg(QString content,int ErrorCode,QHttpRequest *req, QHttpResponse *resp);

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);

    void accumulate();

    void reply();

private:
    QHttpServer *server;

    QHttpRequest* m_req;
    QHttpResponse *m_resp;

signals:
    void sigShutDownAPP();

public slots:
};

#endif // BC_HTTPSERVER_H
