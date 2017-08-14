#ifndef SELFDEF_H
#define SELFDEF_H
#include <QString>
#include <QJsonObject>
#include <QWindow>
#include <QScreen>
#include <QDebug>
#include <QTimer>
#include <QPainter>
//广告播放相关参数
#define INTERVAL_AD 100
#define INTERVAL_ADPause 2000
#define SPEED_AD 0.01
//广告字体
#define FONT_SIZE 20
#define FONT_Family "Helvetica [Cronyx]"
//菜单相关参数
//菜单中的每个控件的款占父控件宽/高大比例
#define SIZE_MENU_W 0.4
#define SIZE_MENU_H 0.2
//购物车中的每个控件的款占父控件宽/高大比例
#define SHOP_MENU_W 0.9
#define SHOP_MENU_H 0.31
//饮料相关参数
#define SIZE_LIST_W 0.1
#define SIZE_LIST_H 0.3
//串口通讯相关
#define INTERVER_Port 1000
#define Baudrate 115200
//一些界面初始化要的时钟
#define INTERVAL_INIT 0.05
//时间原因暂时不研究如何替换3,1
#define FLOAT_STYLE 3.1
//资源链接
#define BACKGROUND_URL ":/image/common/bound.png"

//数据包需要的宏
#define Def_J_GName "J_GName"
#define Def_J_GCapacity "J_GCapacity"
#define Def_J_GWarranty "J_GWarranty"
#define Def_J_GCount "J_GCount"
#define Def_J_GStyle "J_GStyle"
#define Def_J_GBarCode "J_GBarCode"
#define Def_J_DeviceID "J_DeviceID"
#define Def_J_PPayID "J_PPayID"
#define Def_J_PPayNum "J_PPayNum"
#define Def_J_BStateCode "J_BStateCode"

#define Def_J_Account "J_Account"
#define Def_J_Password "J_Password"
#define Def_J_Company "J_Company"
#define Def_J_StaffID "J_StaffID"
#define Def_J_Phonenum "J_Phonenum"
#define Def_J_GDateofBirth "J_GDateofBirth"
#define Def_J_GPrice "J_GPrice"
#define Def_J_GPicURL "J_GPicURL"
#define Def_J_SEARCH "J_SEARCH"


//信号集散中用到的JSON
#define TYPE "Type"
#define COST "Cost"
#define NUM "Num"
#define PLAYTYPE "PLAYTYPE"
#define SUCESS "SUCESS"
//设备号码
#define DEVICEID 0001
#define PAYID    "123456"
//二维码中的服务器IP
#define SERVERIP "http://192.168.1.20:8080/"

//DEBUG
#define DEBUG
#ifdef DEBUG
#define DBUG_OUT qDebug("[%s,%s,%d]",__FILE__,__FUNCTION__,__LINE__)
#endif

//表名
struct GInfo;
struct ADInfo;

enum tableNameList{
    GTable = 0,
    STable,
};

struct GInfo{
    QString Company;
    QString GName;
    QString GDateofBirth;
    QString GWarranty;
    QString GStyle;
    QString GBarCode;
    QString StaffID;
    QString Phonenum;
    QString GPicURL;
    int GCount;
    int GCapacity;
    double GPrice;
    int UserGCount;
};

enum SIGSTYLE{
    PAYSUCESS,//服务器返回的支付成功包
    SHOWAD,//显示AD界面
    CLOSEAD
};
//广告的类型，有图片型号和文字广告
enum ADType{
    PictureAD,
    TextAD
};
//菜单的类型，LIST有选类型菜单和，GRID列举每一种饮料的菜单
enum MenuType{
    ListMenu,
    GridMenu,
    ShoppMenu
};

#endif // SELFDEF_H
