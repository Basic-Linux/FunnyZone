#ifndef CONSOLE_H
#define CONSOLE_H

/*
 * 1 本文档是所有常住元素的所在地
 * 2 同时也是信号的集散地
 * ==============已经实现的功能============
 * 1 能够根据UI查询的SQL信息 发送信号出去
 * 2 能够实现广告界面空闲显示
 * 3 能够在用户点击购买够发送信息给数据库
 * 4 能够操作底层
 * 5 信号集散
 * 集散表格
 * sigCode     意义                               GINFO      json
 * 1    表示请求的什么类型饮料的信息                              Type:soda
 * 2    表示返回的该类型饮料的所有信息
 * 3    表示购买了新的商品，并且要加入购物车
 * 4    表示返回加入购物车的确定信息，此时更新右上角的总价信息        Cost  Num
 * 5    表示请求购物车所有信息
 * 6    表示返回购物车的所有信息
 * 7    表示请求从购物车中增加/撤销某一个商品
 * 8    表示请求出货商品
 * 9    服务器出货成功(关闭二维码)
 * 10   表示请求清楚清楚之前在grid中的widget
 * 11   表示通知UI清楚之前在grid中的widget
*/

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QApplication>
#include "sqlqdata.h"
#include "bc_http.h"
#include "bc_serialport.h"
#include "bcqrcode.h"
#include "selfdef.h"

class SQLQData;

class Console : public QObject{
    Q_OBJECT
private:
    //好像QT中不允许QObject子类为单例模式
    Console(QObject *parent = 0);
    ~Console();

public:
    SQLQData *mdataBase;
    bc_Http *http;
    bc_serialPort * port;

    static Console* getConsoleInstance(){
        static Console console;
        return &console;
    }

signals:
    void sigConsole2UI(int sigCode,GInfo ginfo,QJsonObject obj);

private slots:
    //用来接收来自各个UI的信号并作出相应的决策
    void slotUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);


    void slotDealHttp(QByteArray ary);
    //=======================总资源监察=======================
    void slotTimeOutSty();
    //处理UI到Console的信息
    void slotDealSig(SIGSTYLE style);

public:
    //总体资源
    QList<GInfo> ShoppingCartList;

public:
    //==============各种要用到的方法=========================
    void setScreenSize(QWidget *widget){
        widget->setWindowFlags(Qt::FramelessWindowHint);
        QWindow window;
        QScreen * screen = window.screen();
        widget->resize( screen->size() );
        widget->move(0,0);
    }

    GInfo castSQL2Ginfo(QSqlQuery &sql_query);
    QJsonObject castGinfo2Json(const GInfo &ginfo);
    GInfo castJson2Ginfo(QJsonObject jsonobj);
    void modifyCartList(GInfo ginfo);

    void setSkin()
    {
        //==============使用样式表文件==============
        QFile t_styleSheetFile(":/qss/skin.qss");
        //以只读方式打开文件
        t_styleSheetFile.open(QFile::ReadOnly);
        //读取文件所有内容,用tr()函数将其转换为QString类型
        QString m_styleSheet = QObject::tr(t_styleSheetFile.readAll());
        //为QApplication设置样式表
        qApp->setStyleSheet(m_styleSheet);
    }
    //=======================订单=======================
    QJsonObject generatOrderJson(QJsonArray &obj_array);
    //计算购物车总结
    float calcSumCost(){
        float res = 0;
        for(int i = 0;i < this->ShoppingCartList.count();i++)
        {
            res += ShoppingCartList.at(i).GPrice * ShoppingCartList.at(i).UserGCount;
        }
        return res;
    }
    //=======================支付=======================
    //支付Json
    QJsonObject generatPayJson(double payNum,QString payID);
    bool dealHttpPay(QByteArray ary);
    QImage generateRenCode();
    QString generatePayID(){
        return "123456";
    }
    //=======================服务器=======================
    //发送服务器请求
    void sendMsg2Server(QJsonObject &obj_f);

private:
    bool flagSty;
    QTimer timerSty;

};


#endif // CONSOLE_H
