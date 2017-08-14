#include "bc_http.h"

bc_Http::bc_Http(QObject *parent)
{
    sumArray = new QByteArray;
    tmpArray = new QByteArray;
    manager = new QNetworkAccessManager(parent);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

bc_Http::~bc_Http()
{
    delete manager;
    delete tmpArray;
    delete sumArray;
}

void bc_Http::downloadHttpInfo(QUrl url, QByteArray &data)
{
    //reply = manager->get(QNetworkRequest(url));
    QNetworkRequest request;
    request.setUrl(url);
    //request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray("Sun, 06 Nov 1994 08:49:37 GMT"));
    reply = manager->post(request,data);
}

void bc_Http::replyFinished(QNetworkReply *reply)
{
    sumArray->clear();
    if(reply->error() == QNetworkReply::NoError)    //无错误返回
    {
        while(!reply->atEnd())
        {
            tmpArray->append(reply->read(READSIZE));  //获取字节
            sumArray->append(*tmpArray);
            tmpArray->clear();
        }
    }
    qDebug() << "sumArray" << *sumArray;
    reply->deleteLater();
    emit bc_ReplyFinished(*sumArray);
}


