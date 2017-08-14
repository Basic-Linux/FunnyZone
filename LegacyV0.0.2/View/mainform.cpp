#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->showFullScreen();

    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));

    connect(Console::getConsoleInstance(),SIGNAL(sigConsole2UI(int,GInfo,QJsonObject)),
            this,SLOT(slotConsole2UI(int,GInfo,QJsonObject)));

    //Default
    ui->widget_Menu->setMenuType(ListMenu);
    ui->widget_List->setMenuType(GridMenu);

    //初始化
    ui->widget_Menu->setMenuType(ListMenu);
    GInfo ginfo;
    ginfo.GStyle = "汽水";
    ui->widget_Menu->addElement(ginfo);
    ginfo.GStyle = "牛奶";
    ui->widget_Menu->addElement(ginfo);
    ginfo.GStyle = "果汁";
    ui->widget_Menu->addElement(ginfo);
    ginfo.GStyle = "茶饮";
    ui->widget_Menu->addElement(ginfo);
    ginfo.GStyle = "咖啡";
    ui->widget_Menu->addElement(ginfo);

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::slotConsole2UI(int sigCode, GInfo ginfo, QJsonObject obj)
{
    if(sigCode == 2)
    {
        ui->widget_List->addElement(ginfo);
    }
    else if(sigCode == 4)
    {
        const float cost = obj[COST].toDouble();
        const int num = obj[NUM].toInt();

        QString str = QString::asprintf("总数 %d  总价%3.0f 元",num,cost);
        ui->label_Cost->setText(str);
    }
    else if(sigCode == 11)
    {
        ui->widget_List->removePreWidgets();
    }
}

void MainForm::on_pushButton_Back_clicked()
{
    WelcomUI *widget = new WelcomUI;
    widget->show();
    this->close();
}

void MainForm::on_pushButton_calc_clicked()
{
    //打开购物车
    ShoppingCartUI *widget = new ShoppingCartUI;
    widget->show();
    this->close();
}
