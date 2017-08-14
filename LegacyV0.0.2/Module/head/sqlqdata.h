#ifndef QSLQDATA_H
#define QSLQDATA_H
#define SQLDATABASENAME "database.db"
#define SQLUSERNAME "root"
#define SQLUSERPASSWD "123456"
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QJsonObject>
#include "xmlparse.h"
#include "selfdef.h"
#include "console.h"

/*
 * 总表表格式：
 * ID   GCompany  GName GCapacity GDateofBirth GWarranty GCount GStyle GBarCode
 * int                                        int        int
 * 广告表格式：
 * ID   GCompany  GName PlayTime
 * int                 int
 * 货物表格式：
 * ID   GCompany  GName GCapacity GDateofBirth GWarranty GCount GStyle GBarCode
 * int                                        int        int
 * 入货表格式：
 * ID   GCompany  GName GCapacity GDateofBirth GWarranty GCount GStyle GBarCode StaffID Phonenum
 * int                                        int        int
 * 出货表格式：
 * ID   GCompany  GName GCapacity GDateofBirth GWarranty GCount GStyle GBarCode StaffID Phonenum
 * int
*/
class SQLQData : public QObject
{
    Q_OBJECT

public:
    QSqlDatabase database;
    QSqlQuery sql_query;
    SQLQData();
    ~SQLQData();
    void initSQLDatabase();     //ok
    bool initSumDatatable();  //ok

    bool creatResDatatable();//ok
    void initResDatatable();//ok

    QSqlQuery searchSQLInfo(QString select_sql_); //ok
    bool controlSQLInfo(QString select_sql_);//ok

    //获取该类型商品的数量
    int getGTypeCount(QString gtype);//ok
    //获取该类型商品的所有信息
    QSqlQuery getGTypeGInfo(QString gtype);//ok
    //获取该名商品的数量
    int getGNameCount(QString gname);//ok
    //获取该名商品的图片信息
    QString getGNamePicUrl(QString gname);//ok

    bool addSQLInfo(tableNameList table,QJsonObject jsonobj);//ok

    void releaseSQLDatabase();
    void removeSQLInfo();
    void modifySQLInfo();
    void initSourceDatabase();

signals:
    void updatedSQL(tableNameList,QJsonObject jsonobj);
};

#endif // QSLQDATA_H
