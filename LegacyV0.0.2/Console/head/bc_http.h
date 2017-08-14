#ifndef BC_HTTP_H
#define BC_HTTP_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>

#define READSIZE 1024

class bc_Http : public QObject
{
    Q_OBJECT

public:
    bc_Http(QObject *parent = 0);
    ~bc_Http();

    void downloadHttpInfo(QUrl url, QByteArray &data);

protected slots:
    void replyFinished(QNetworkReply *reply);

signals:
    void bc_ReplyFinished(QByteArray sumArray);

private:
    QByteArray *sumArray;
    QByteArray *tmpArray;

    QNetworkAccessManager * manager;
    QNetworkReply * reply;

};

#endif // BC_HTTP_H
