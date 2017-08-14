#include "sqlqdata.h"


SQLQData::SQLQData() : QObject()
{
}

SQLQData::~SQLQData()
{
}

void SQLQData::initSQLDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(SQLDATABASENAME);
    database.setUserName(SQLUSERNAME);
    database.setPassword(SQLUSERPASSWD);
    if(!database.open())
    {
        qDebug() << database.lastError();
        qFatal("failed to connect.") ;
    }
    sql_query = QSqlQuery(database);
    DBUG_OUT;
}

bool SQLQData::initSumDatatable()
{
    QString create_sql = "create table SumTable (ID INTEGER primary key AUTOINCREMENT ,"
                         "GNAME varchar(30),"
                         "GCompany varchar(30),"
                         "GCapacity int,"
                         "GDateofBirth varchar(30),"
                         "GWarranty varchar(30),"
                         "GCount int,"
                         "GStyle varchar(30),"
                         "GBarCode varchar(30),"
                         "StaffID varchar(30),"
                         "Phonenum varchar(30),"
                         "GPrice double)";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<" SUM table created!";
        return true;
    }
    DBUG_OUT;
}

bool SQLQData::creatResDatatable()
{
    //bad deal GPicUrl may leak of lenth
    //创建资源列表
    QString create_sql = "create table ResTable (ID INTEGER primary key AUTOINCREMENT ,"
                 "NAME varchar(30),"
                 "PATCH varchar(1024))";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<" RES table created!";
        return true;
    }
}

void SQLQData::initResDatatable()
{
    //给资源数据库添加数据
    if(creatResDatatable())
    {
        QMap<QString,QString> map;
        QString xmlPath = QDir::currentPath() + "/res.xml";
        map = XmlParse::getInfoList(xmlPath);
        qDebug() << map;
        QList<QString> keys = map.keys();
        QList<QString> values = map.values();
        for(int i = 0;i< map.count();i++)
        {
            QString name = keys.at(i);
            QString path = values.at(i);
            QString control_sql__ = QString::asprintf("insert into ResTable (NAME,PATCH) values ('%s','%s')",
                                                      name.toStdString().c_str(),path.toStdString().c_str());
            controlSQLInfo(control_sql__);
        }
    }
}

bool SQLQData::controlSQLInfo(QString select_sql_)
{
    QString select_sql = select_sql_;
    if(!sql_query.exec(select_sql))
    {
        qDebug()<< sql_query.lastError();
        return false;
    }
    else
    {
        qDebug()<<"table control sucess!";
        return true;
    }
}

int SQLQData::getGTypeCount(QString gtype)
{
    QString sqlString = QString::asprintf("select count(*) from SumTable where GStyle='%s'",gtype.toStdString().c_str());
    QSqlQuery sql_query = searchSQLInfo(sqlString);
    sql_query.next();
//    qDebug() << "sqllen = " << sqlLen;
    return sql_query.value(0).toInt();
    DBUG_OUT;
}

int SQLQData::getGNameCount(QString gname)
{
    QString sqlString = QString::asprintf("select * from SumTable where GName='%s'",gname.toStdString().c_str());
    QSqlQuery sql_query_ = searchSQLInfo(sqlString);
    int count = 0;
    while(sql_query_.next())
    {
        sql_query_.value("GCount").toInt();
        count ++ ;
    }
    return count;
}

QString SQLQData::getGNamePicUrl(QString gname)
{
    QString sqlString = QString::asprintf("select * from ResTable where NAME='%s'",gname.toStdString().c_str());
    QSqlQuery sql_query_ = searchSQLInfo(sqlString);
    sql_query_.next();
    return sql_query_.value("PATCH").toString();
}

QSqlQuery SQLQData::getGTypeGInfo(QString gtype)
{
    QString sqlString = QString::asprintf("select * from SumTable where GStyle='%s'",gtype.toStdString().c_str());
    return searchSQLInfo(sqlString);
}

bool SQLQData::addSQLInfo(tableNameList table,QJsonObject jsonobj)
{
    struct GInfo ginfo;
    switch(table)
    {
    case GTable:
        ginfo = Console::getConsoleInstance()->castJson2Ginfo(jsonobj);
        QString insert_sql = QString::asprintf("insert into SumTable (GNAME,GCompany,GDateofBirth,GWarranty,GStyle,"
                                                       "GBarCode,StaffID,Phonenum,GCapacity,GCount,GPrice) "
                                                       "values ('%s','%s','%s','%s','%s','%s','%s','%s','%d','%d','%f')"
                                                       ,ginfo.GName.toStdString().c_str(),ginfo.Company.toStdString().c_str(),ginfo.GDateofBirth.toStdString().c_str(),
                                                       ginfo.GWarranty.toStdString().c_str(),ginfo.GStyle.toStdString().c_str(),ginfo.GBarCode.toStdString().c_str(),
                                                       ginfo.StaffID.toStdString().c_str(),ginfo.Phonenum.toStdString().c_str(),ginfo.GCapacity,
                                                       ginfo.GCount,ginfo.GPrice);

        sql_query.prepare(insert_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
            return false;
        }
        else
        {
            qDebug()<<"inserted!";
            jsonobj = Console::getConsoleInstance()->castGinfo2Json(ginfo);
            emit updatedSQL(GTable,jsonobj);
            return true;
        }

        break;
    }
    DBUG_OUT;
}

QSqlQuery SQLQData::searchSQLInfo(QString select_sql_)
{
    QString select_sql = select_sql_;
    if(!sql_query.exec(select_sql))
    {
        qDebug()<< sql_query.lastError();
    }
    else
    {
        return sql_query;
    }

    sql_query.clear();

    DBUG_OUT;
    return sql_query;
}

//    QJsonObject jsonobj;
//    QString select_sql;
//    struct GInfo ginfo;
//    QString result;
//    switch(table)
//    {
//    case GTable:
//        qDebug("Gtable SQL");
//        select_sql = info;
//        if(!sql_query.exec(select_sql))
//        {
//            qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//            while(sql_query.next())
//            {
//                ginfo.GName = sql_query.value("GNAME").toString();
//                ginfo.Company = sql_query.value("GCompany").toString();
//                ginfo.GDateofBirth = sql_query.value("GDateofBirth").toString();
//                ginfo.GWarranty = sql_query.value("GWarranty").toString();
//                ginfo.GStyle = sql_query.value("GStyle").toString();
//                ginfo.GBarCode = sql_query.value("GBarCode").toString();
//                ginfo.StaffID = sql_query.value("StaffID").toString();
//                ginfo.Phonenum = sql_query.value("Phonenum").toString();
//                ginfo.GCapacity = sql_query.value("GCapacity").toInt();
//                ginfo.GCount = sql_query.value("GCount").toInt();
//                ginfo.GPrice = sql_query.value("GPrice").toFloat();
//            }
//            jsonobj = commontFunc::castGInfo2Json(ginfo);
//            return jsonobj;
//        }

//        break;

//    case STable:
//        select_sql = QString::asprintf("select PATCH from SourceTable top1 where NAME='%s'",
//                                       jsonobj.take(Def_J_SEARCH).toString().toStdString().c_str());
//        if(!sql_query.exec(select_sql))
//        {
//            qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//            while(sql_query.next())
//            {
//                result = sql_query.value("PATCH").toString();
//            }
//            jsonobj.insert(Def_J_GPicURL,result);
//            return jsonobj;
//        }
//        break;
//    }

//    switch(table)
//    {
//    case GTable:
//        qDebug("Gtable SQL");
//        select_sql = info;
//        if(!sql_query.exec(select_sql))
//        {
//            qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//            while(sql_query.next())
//            {
//                ginfo.GName = sql_query.value("GNAME").toString();
//                ginfo.Company = sql_query.value("GCompany").toString();
//                ginfo.GDateofBirth = sql_query.value("GDateofBirth").toString();
//                ginfo.GWarranty = sql_query.value("GWarranty").toString();
//                ginfo.GStyle = sql_query.value("GStyle").toString();
//                ginfo.GBarCode = sql_query.value("GBarCode").toString();
//                ginfo.StaffID = sql_query.value("StaffID").toString();
//                ginfo.Phonenum = sql_query.value("Phonenum").toString();
//                ginfo.GCapacity = sql_query.value("GCapacity").toInt();
//                ginfo.GCount = sql_query.value("GCount").toInt();
//                ginfo.GPrice = sql_query.value("GPrice").toFloat();
//            }
//            jsonobj = commontFunc::castGInfo2Json(ginfo);
//            return jsonobj;
//        }

//        break;

//    DBUG_OUT;
//}
void SQLQData::releaseSQLDatabase()
{
    QString clear_sql = "delete from SumTable";

    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"cleared";
    }
    database.close();
    QFile::remove("database.db");
}
void SQLQData::initSourceDatabase()
{
    QString tmp_sql = "create table SourceTable (ID INTEGER primary key AUTOINCREMENT ,NAME varchar(30),PATCH varchar(30))";
    sql_query.prepare(tmp_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"initSourceDatabase!";
    }
    tmp_sql = "insert into SourceTable (NAME,PATCH) values ('Cocol',':/pic.jpg')";
    sql_query.prepare(tmp_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"inserted SourceDatabase!";
    }
    DBUG_OUT;
}
