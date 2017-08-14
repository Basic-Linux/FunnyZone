#include "qrencodewidget.h"
#include "ui_qrencodewidget.h"

qrencodeWidget::qrencodeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qrencodeWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);

    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));
    connect(Console::getConsoleInstance(),SIGNAL(sigConsole2UI(int,GInfo,QJsonObject)),
            this,SLOT(slotConsole2UI(int,GInfo,QJsonObject)));

}

qrencodeWidget::qrencodeWidget(QImage image, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qrencodeWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setRencode(image);
    this->showFullScreen();

    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));
    connect(Console::getConsoleInstance(),SIGNAL(sigConsole2UI(int,GInfo,QJsonObject)),
            this,SLOT(slotConsole2UI(int,GInfo,QJsonObject)));


//    timer.start();
}

qrencodeWidget::~qrencodeWidget()
{
    delete ui;
}

void qrencodeWidget::setRencode(QImage &pic)
{
    ui->label->setAlignment(Qt::AlignHCenter);
    pix.convertFromImage(pic);
    ui->label->setPixmap(pix);
}

void qrencodeWidget::showPaySucess()
{
    MainForm *mainform = new MainForm;
    mainform->show();
    this->close();
}

void qrencodeWidget::on_pushButton_clicked()
{
    GInfo ginfo;
    QJsonObject obj;
    emit sigUI2Console(8,ginfo,obj);
    MainForm *mainform = new MainForm;
    mainform->show();
    this->close();
}

void qrencodeWidget::slotConsole2UI(int sigCode, GInfo ginfo, QJsonObject obj)
{
    if(sigCode == 9)
    {
        showPaySucess();
    }
}
