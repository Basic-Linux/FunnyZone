#ifndef XMLPARSE_H
#define XMLPARSE_H

#include <QObject>
#include <QFile>
#include <QDomElement>
#include <QDomNode>
#include <QMessageBox>
#include <QDebug>

class XmlParse : public QObject
{
    Q_OBJECT
public:
    explicit XmlParse(QObject *parent = 0);
    ~XmlParse();

    //获取XML的key值和对应的value值序列
    static QMap<QString,QString> getInfoList(QString xmlPath);
signals:

public slots:
};

#endif // XMLPARSE_H
