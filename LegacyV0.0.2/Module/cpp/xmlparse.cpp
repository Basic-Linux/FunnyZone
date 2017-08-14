#include "xmlparse.h"

XmlParse::XmlParse(QObject *parent) : QObject(parent)
{

}

XmlParse::~XmlParse()
{

}

QMap<QString, QString> XmlParse::getInfoList(QString xmlPath)
{
    QMap<QString, QString> map;
    if(xmlPath.isEmpty())
    {
        QMessageBox::warning(NULL, QString("xml parse"), QString("path null!"));
        return map;
    }

    QFile file(xmlPath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(NULL, QString("xml parse"), QString("open error!"));

        return map;
    }

    QDomDocument document;
    QString error;
    int row = 0, column = 0;
    //加载xml
    if(!document.setContent(&file, false, &error, &row, &column))
    {
        QMessageBox::information(NULL, QString("xml parse"), QString("parse file failed at line row and column") + QString::number(row, 10) + QString(",") + QString::number(column, 10));
        return map;
    }

    if(document.isNull())
    {
        QMessageBox::information(NULL, QString("xml parse"), QString("document is null!"));
        return map;
    }

    //获取root节点
    QDomElement root = document.documentElement();

    //root_tag_name为persons
    QString root_tag_name = root.tagName();
    qDebug() << "root_tag_name = "<< root_tag_name;

    //获取root下的第一个body array
    QDomElement firstNode = root.firstChildElement();
    if(firstNode.isNull())
        return map;

//    QString person_tag_name = firstNode.tagName();

//    qDebug() << "person_tag_name  = "<< person_tag_name;

    QDomNodeList list = root.childNodes();

    qDebug() << "list  = "<< list.count();
    //获取res下所有的dict节点
    for(int i = 0;i < list.count();i++)
    {
        QString name,path;
        //获取 dict节点
        QDomNode dom_node = list.item(i);
        QDomElement element = dom_node.toElement();
        if(element.tagName() != "dict")
        {
            QMessageBox::information(NULL, QString("xml parse"), QString("xml format er!"));
            return map;
        }
        //获取 dict节点下的子节点 key 和 string
        QDomNodeList child_list = element.childNodes();
        for(int j = 0;j < child_list.count();j++)
        {
            QDomNode child_dom_node = child_list.item(j);
            QDomElement child_element = child_dom_node.toElement();
            if(child_element.tagName() == "name")
            {
                name = child_element.text();
            }
            else if(child_element.tagName() == "path")
            {
                path = child_element.text();
            }
        }
        map.insert(name,path);
    }

    return map;
}
