#include "console.h"

Console::Console(QObject *parent) : QObject(parent),mdataBase (new SQLQData)
{
    //init sql
    mdataBase = new SQLQData;
    mdataBase->initSQLDatabase();
    mdataBase->initSumDatatable();
    mdataBase->initResDatatable();
    //http
    http = new bc_Http;
    connect(http,SIGNAL(bc_ReplyFinished(QByteArray)),this,SLOT(slotDealHttp(QByteArray)));
    //新建出serial port
    port = new bc_serialPort;
    port->setPort(115200);

    //对于总体资源监察
    //是否待机
    flagSty = true;
}

Console::~Console()
{

}

void Console::slotUI2Console(int sigCode, GInfo ginfo, QJsonObject obj)
{
    /*sigCode     意义                          GINFO      json
     * 1    表示请求的什么类型饮料的信息
     * 2    表示返回的该类型饮料的所有信息
     * */
//    qDebug("%s");
    int i = 0;
    if(sigCode == 1)
    {
        //str是饮料的类型，比如说 汽水
        QString str = ginfo.GStyle;
//        QString str = obj[TYPE].toString();
        int sqlLen = mdataBase->getGTypeCount(str);
        //如果检索该类商品少于0个 则返回
        if(sqlLen <= 0)
        {
            return ;
        }
        //获取该类型商品的所有信息
        QSqlQuery sql_query = mdataBase->getGTypeGInfo(str);

        while(sql_query.next() && i < sqlLen)
        {
            struct GInfo ginfo = this->castSQL2Ginfo(sql_query);
            //ginfo即是获取到的饮料的信息
            QJsonObject obj;
            emit sigConsole2UI(2,ginfo,obj);
        }
    }
    else if(sigCode == 3)
    {
        modifyCartList(ginfo);
        float sum = this->calcSumCost();
        GInfo ginfo;
        QJsonObject obj;
        obj.insert(COST,sum);
        int num = 0;
        for(int i = 0;i < this->ShoppingCartList.count();i++)
        {
            num += this->ShoppingCartList.at(i).UserGCount;
        }
        obj.insert(NUM,num);
        emit sigConsole2UI(4,ginfo,obj);
    }
    else if(sigCode == 5)
    {
        for(int i = 0; i < this->ShoppingCartList.count();i++)
        {
            QJsonObject obj;
            emit sigConsole2UI(6,ShoppingCartList.at(i),obj);
        }
    }
    else if(sigCode == 7)
    {
//        qDebug() << "ginfo cout" << ginfo.UserGCount;
        modifyCartList(ginfo);
    }
    else if(sigCode == 8)
    {
        QJsonArray obj_array;
        for(int i = 0;i < ShoppingCartList.count();i++)
        {
            QJsonObject obj_c = castGinfo2Json(ShoppingCartList.at(i));
            obj_array.append(obj_c);
        }
        QJsonObject obj_f = generatOrderJson(obj_array);
        //向服务端口发送信息
        sendMsg2Server(obj_f);
    }
    else if(sigCode == 10)
    {
        GInfo ginfo;
        QJsonObject obj;
        emit sigConsole2UI(11,ginfo,obj);
    }
}

GInfo Console::castSQL2Ginfo(QSqlQuery &sql_query)
{
    struct GInfo ginfo;

    ginfo.GName = sql_query.value("GNAME").toString();
    ginfo.Company = sql_query.value("GCompany").toString();
    ginfo.GDateofBirth = sql_query.value("GDateofBirth").toString();
    ginfo.GWarranty = sql_query.value("GWarranty").toString();
    ginfo.GStyle = sql_query.value("GStyle").toString();
    ginfo.GBarCode = sql_query.value("GBarCode").toString();
    ginfo.StaffID = sql_query.value("StaffID").toString();
    ginfo.Phonenum = sql_query.value("Phonenum").toString();
    ginfo.GCapacity = sql_query.value("GCapacity").toInt();
    //获取商品数量
    ginfo.GCount = mdataBase->getGNameCount(ginfo.GName);
    ginfo.GPrice = sql_query.value("GPrice").toFloat();
    //获取商品的图片
    ginfo.GPicURL = mdataBase->getGNamePicUrl(ginfo.GName);

    return ginfo;
}

QJsonObject Console::castGinfo2Json(const GInfo &ginfo)
{
    QJsonObject obj_c;
    obj_c.insert("J_DeviceID",DEVICEID);
    obj_c.insert("J_GName",ginfo.GName);
    obj_c.insert("J_GCapacity",ginfo.GCapacity);
    obj_c.insert("J_GWarranty",ginfo.GWarranty);
    obj_c.insert("J_GCount",ginfo.GCount);
    obj_c.insert("J_GStyle",ginfo.GStyle);
    obj_c.insert("J_GBarCode",ginfo.GBarCode);
    obj_c.insert("J_PPayNum",ginfo.GPrice);
    obj_c.insert("J_PPayID",PAYID);
    return obj_c;
}

GInfo Console::castJson2Ginfo(QJsonObject jsonobj)
{
    struct GInfo ginfo;

    ginfo.GName = jsonobj.take(Def_J_GName).toString();
    ginfo.Company = jsonobj.take(Def_J_Company).toString();
    ginfo.GDateofBirth = jsonobj.take(Def_J_GDateofBirth).toString();
    ginfo.GWarranty = jsonobj.take(Def_J_GWarranty).toString();
    ginfo.GStyle = jsonobj.take(Def_J_GStyle).toString();
    ginfo.GBarCode = jsonobj.take(Def_J_GBarCode).toString();
    ginfo.StaffID = jsonobj.take(Def_J_StaffID).toString();
    ginfo.Phonenum = jsonobj.take(Def_J_Phonenum).toString();
    ginfo.GCapacity = jsonobj.take(Def_J_GCapacity).toInt();
    ginfo.GPrice = jsonobj.take(Def_J_GPrice).toDouble();
    ginfo.GCount = jsonobj.take(Def_J_GCount).toInt();

    return ginfo;
}

void Console::modifyCartList(GInfo ginfo)
{
    for(int i = 0; i < this->ShoppingCartList.count();i++)
    {
        if(ShoppingCartList.at(i).GName == ginfo.GName)
        {
            ShoppingCartList.replace(i,ginfo);
            return ;
        }
    }

    ShoppingCartList.append(ginfo);
}

QJsonObject Console::generatOrderJson(QJsonArray &obj_array)
{
    QJsonObject obj_f;
    obj_f.insert("J_POrder",obj_array);
    qDebug() << obj_f;

    return obj_f;
}

QJsonObject Console::generatPayJson(double payNum, QString payID)
{
    QJsonObject obj_p;
    obj_p.insert("J_BankIP",SERVERIP);
    obj_p.insert("J_PPayNum",payNum);
    obj_p.insert("J_PPayID",payID);
    QJsonObject obj_pf;
    obj_pf.insert("J_PPayment",obj_p);

    return obj_pf;
}

bool Console::dealHttpPay(QByteArray ary)
{
    QJsonObject json_obj_sum = QJsonDocument::fromJson(ary).object();
    QJsonObject json_obj = json_obj_sum.take("J_BPPayment").toObject();

    if(json_obj.take("J_BStateCode").toInt() == 1)
    {
        return true;
    }
    else
        return false;
}

QImage Console::generateRenCode()
{
    //产生二维码
    int SumPayNum = calcSumCost();
    QString payID = generatePayID();
    //根据商品数确定金额
    QJsonObject obj_pf = generatPayJson(SumPayNum,payID);
    //这里的常量可以随意设置一个大于零的数即可
    QImage qrcode = MQRcode::GenerateQRcodeImage( QString(QJsonDocument(obj_pf).toJson()),QSize(300,300));
    return qrcode;
}

void Console::sendMsg2Server(QJsonObject &obj_f)
{
    QString buf = SERVERIP;
    QString data = QString(QJsonDocument(obj_f).toJson());
    QByteArray data_bit = QByteArray(data.toStdString().c_str());
    qDebug() << "buf = " << buf;
    buf = buf + data;
    http->downloadHttpInfo(QUrl(buf),data_bit);
}

void Console::slotDealHttp(QByteArray ary)
{
//    QJsonObject obj;
//    obj.insert("J_DeviceID",0001);
//    obj.insert("J_PPayID",123456789);
//    obj.insert("J_BStateCode",1);
//    QJsonObject obj_sum;
//    obj_sum.insert("J_BPPayment",obj);
//    ary.clear();
//    QString data = QString(QJsonDocument(obj_sum).toJson());
//    ary = QByteArray(data.toStdString().c_str());
//    qDebug() << "ary = " << ary;

    //收到数据后进行数据解析
    if( dealHttpPay(ary) )
    {
        //方向一:向UI
        GInfo ginfo;
        QJsonObject obj;
        obj.insert(PLAYTYPE,SUCESS);
        emit sigConsole2UI(9,ginfo,obj);
//        emit sigConsole2UI(PAYSUCESS);
        //方向二：向底层
        QByteArray array = ":A1030501560D0A";
        port->writePort(array);
        DBUG_OUT;
    }
}

void Console::slotTimeOutSty()
{
        //flagSty = false;
//        emit sigConsole2UI(SHOWAD);
        timerSty.stop();
        DBUG_OUT;
}

void Console::slotDealSig(SIGSTYLE style)
{
    if(style == CLOSEAD)
        timerSty.start();
}
