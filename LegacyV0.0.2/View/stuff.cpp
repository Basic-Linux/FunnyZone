#include "stuff.h"
#include "ui_stuff.h"

Stuff::Stuff(GInfo &ginfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stuff)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->ginfo = ginfo;
    this->ginfo.UserGCount = 0;
//    qDebug() << ginfo.GPrice;

    //初始化UI界面
    QString price = QString::asprintf("单价:%3.1f元/瓶",ginfo.GPrice);
    ui->lineEdit_price->setText(price);
//    this->setPic(ginfo.GPicURL);
    ui->widget_pic->setPixmap(ginfo.GPicURL);

//    timerInit.setSingleShot(true);
//    connect(&timerInit,SIGNAL(timeout()),this,SLOT(slotTimerOut()));
//    timerInit.start(INTERVAL_INIT);
}

Stuff::~Stuff()
{
    delete ui;
}

//设置货物图片
//void Stuff::setPic(QString url)
//{
//    QString sheet = QString::asprintf("border-image: url(%s);"
//                                      ,url.toStdString().c_str());
//    ui->widget_pic->setStyleSheet(sheet);
//}

GInfo &Stuff::getGinfo()
{
    return ginfo;
}

QString Stuff::getGName()
{
    return ginfo.GName;
}

void Stuff::mouseReleaseEvent(QMouseEvent *event)
{
    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));
    QJsonObject obj;
    this->ginfo.UserGCount++;
    emit sigUI2Console(3,this->ginfo,obj);
    disconnect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));
}
