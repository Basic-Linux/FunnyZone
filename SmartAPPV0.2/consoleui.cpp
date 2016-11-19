#include "consoleui.h"
#include "ui_consoleui.h"
#include "ui_threeWidget.h"
#include <QJsonDocument>

consoleUI::consoleUI(controlModule *wh_control,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::consoleUI)
{
    //UI
    ui->setupUi(this);
//    this->resize(CONSOLESIZE);
    threeLayout = new QHBoxLayout(ui->wigetThree);
    threewidget = new threeWidget();
    threeLayout->addWidget((QWidget *)threewidget);
    doorwidget = new selfWidget(":/res/opendoor_ico2.png",":/res/closedoor_ico2.png",ui->doorWidget->size(),ui->doorWidget);
    fanwidget = new moveWidget(":/res/fan_ico3.png",ui->controlWidget->size(),ui->controlWidget);
    led1widget = new selfWidget(":/res/openled_ico2.png",":/res/closeled_ico2.png",ui->led1Widget->size(),ui->led1Widget);
    led2widget = new selfWidget(":/res/openled_ico2.png",":/res/closeled_ico2.png",ui->led2Widget->size(),ui->led2Widget);
    image = new QPixmap(":/res/background_6.png");
    *image = image->scaled(this->size());
    this->setWindowTitle(tr("SmartApp"));
    dragPos = new QPoint();
    //func
    doorFlag = false;
    fanFlag = false;
    led1Flag = false;
    led2Flag = false;
    this->wh_control = wh_control;
    connect(this->fanwidget,SIGNAL(clicked(QWidget*)),this,SLOT(ctlDataSend(QWidget*)));
    connect(this->doorwidget,SIGNAL(clicked(QWidget*)),this,SLOT(ctlDataSend(QWidget*)));
    connect(this->led1widget,SIGNAL(clicked(QWidget*)),this,SLOT(ctlDataSend(QWidget*)));
    connect(this->led2widget,SIGNAL(clicked(QWidget*)),this,SLOT(ctlDataSend(QWidget*)));
    connect(this->threewidget,SIGNAL(clicked(QWidget*)),this,SLOT(ctlDataSend(QWidget*)));
    connect(wh_control,SIGNAL(sigDataRecved(uint8_t,QJsonObject)),this,SLOT(ctlDataRecved(uint8_t,QJsonObject)));
    thr = new myThread(this->wh_control,parent);
    thr->start(QThread::NormalPriority);
}
consoleUI::~consoleUI()
{
    thr->terminate();
    delete ui;
}
void consoleUI::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton)
    {
        *dragPos = e->globalPos() - frameGeometry().topLeft();
        e->accept();
    }
}
void consoleUI::mouseMoveEvent(QMouseEvent * e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - *dragPos);
        e->accept();
    }
}
//void consoleUI::paintTitle(QImage *pixmap,QWindow)
//{
//    QPainter painter(this);
//    painter.fillRect(0,0,this->width(),this->height(),*pixmap);
//}
void consoleUI::paintBackground(QPixmap *pixmap)
{
    QPainter painter(this);
    //painter.fillRect(0,0,this->width(),this->height(),QPixmap(":/res/background_2.jpg"));
    this->setMask(pixmap->mask());
    painter.fillRect(0,0,this->width(),this->height(),*pixmap);
}
void consoleUI::ctlDataSend(QWidget* widget)
{
    QJsonObject json_object;
    json_object.insert(J_userName,"111");
    json_object.insert(J_password,"111");
    json_object.insert(J_userToken,userToken);

    qDebug() << "ctlDataSenduserToken = " << userToken;
    if(( widget == fanwidget ) )
    {
        fanFlag = !fanFlag;
        if(fanFlag)
        {
            fanwidget->roateFlag = true;
            fanwidget->update();
            json_object.insert(J_deviceCode,0);
            json_object.insert(J_deviceNumber,0);
            wh_control->socketdataSend(CTLFAN,json_object);
        }
        else
        {
            fanwidget->roateFlag = false;
            fanwidget->update();
            json_object.insert(J_deviceCode,1);
            json_object.insert(J_deviceNumber,0);
            wh_control->socketdataSend(CTLFAN,json_object);
        }
    }


    if(( widget == doorwidget ) )
    {
        doorFlag = !doorFlag;
        if(doorFlag)
        {
            doorwidget->stateFlag = true;
            doorwidget->update();
            json_object.insert(J_deviceCode,0);
            json_object.insert(J_deviceNumber,0);
            wh_control->socketdataSend(CTLDOOR,json_object);
        }
        else
        {
            doorwidget->stateFlag = false;
            doorwidget->update();
            json_object.insert(J_deviceCode,1);
            json_object.insert(J_deviceNumber,0);
            wh_control->socketdataSend(CTLDOOR,json_object);
        }
    }


    if(( widget == led1widget ) )
    {
        led1Flag = !led1Flag;
        if(led1Flag)
        {
            led1widget->stateFlag = true;
            led1widget->update();
            json_object.insert(J_deviceCode,0);
            json_object.insert(J_deviceNumber,0);
            wh_control->socketdataSend(CTLLED,json_object);
        }
        else
        {
            led1widget->stateFlag = false;
            led1widget->update();
            json_object.insert(J_deviceCode,1);
            json_object.insert(J_deviceNumber,0);
            wh_control->socketdataSend(CTLLED,json_object);
        }
    }

    if(( widget == led2widget ) )
    {
        led2Flag = !led2Flag;
        if(led2Flag)
        {
            led2widget->stateFlag = true;
            led2widget->update();
            json_object.insert(J_deviceCode,0);
            json_object.insert(J_deviceNumber,1);
            wh_control->socketdataSend(CTLLED,json_object);
        }
        else
        {
            led2widget->stateFlag = false;
            led2widget->update();
            json_object.insert(J_deviceCode,1);
            json_object.insert(J_deviceNumber,1);
            wh_control->socketdataSend(CTLLED,json_object);
        }
    }
//    if(( widget == threewidget ))
//    {
//        json_object.insert(J_deviceNumber,0);
//        wh_control->socketdataSend(CTLTEMP,json_object);
//        wh_control->socketdataSend(CTLHUM,json_object);
//        wh_control->socketdataSend(CTLLUX,json_object);
//    }


    DBUG_OUT;
}
void consoleUI::ctlDataRecved(uint8_t taskID,QJsonObject json)
{
#ifdef DEBUG
    qDebug() << "ctlDataRecved recv msg = %s" << QString(QJsonDocument(json).toJson());
#endif
    int text = 0;
    switch (taskID) {
    case CTLTEMP:
        text = json.take(J_temperature).toInt();
        qDebug() << J_temperature << text;
        threewidget->ui->lineEdit_temp->setText(QString::number(text));
        break;
    case CTLHUM:
        text = json.take(J_humidity).toInt();
        qDebug() << J_humidity << text;
        threewidget->ui->lineEdit_hum->setText(QString::number(text));
        break;
    case CTLLUX:
        text = json.take(J_light).toInt();
        qDebug() << J_humidity << text;
        threewidget->ui->lineEdit_light->setText(QString::number(text));
        break;
    default:
        break;
    }
    DBUG_OUT;
}
void consoleUI::paintEvent(QPaintEvent *)
{
    paintBackground(image);
}
