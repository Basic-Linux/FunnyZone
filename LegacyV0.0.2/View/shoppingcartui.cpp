#include "shoppingcartui.h"
#include "ui_shoppingcartui.h"

ShoppingCartUI::ShoppingCartUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingCartUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->showFullScreen();
//    this->setWindowOpacity(0.5);
//    ui->widget->setWindowOpacity(1);
    //连接信号与槽
    ui->widgetMenu->setMenuType(ShoppMenu);

    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));

    connect(Console::getConsoleInstance(),SIGNAL(sigConsole2UI(int,GInfo,QJsonObject)),
            this,SLOT(slotConsole2UI(int,GInfo,QJsonObject)));

    GInfo ginfo;
    QJsonObject obj;
    emit sigUI2Console(5,ginfo,obj);
}

ShoppingCartUI::~ShoppingCartUI()
{
    delete ui;
}

void ShoppingCartUI::slotConsole2UI(int sigCode, GInfo ginfo, QJsonObject obj)
{
    if(sigCode == 6)
    {
        for(int i = 0; i < this->ShoppingCartList.count();i++)
        {
            //这个步骤主要有两个功能：1 刷新widget
            if(this->ShoppingCartList.at(i).GName == ginfo.GName)
            {
                //1 刷新widget
                MenuWidget * widget = dynamic_cast<MenuWidget *>( ui->widgetMenu->getLayout()->itemAt(i)->widget() );
                if(widget)
                    widget->addGcount();
                this->ShoppingCartList.append(ginfo);
                return ;
            }
        }

        this->ShoppingCartList.append(ginfo);
        ui->widgetMenu->addElement(ginfo);
    }
}

void ShoppingCartUI::on_pushButtonClear_clicked()
{
    GInfo ginfo;
    QJsonObject obj;
    emit sigUI2Console(8,ginfo,obj);

    QImage image = Console::getConsoleInstance()->generateRenCode();
    qrencodeWidget * widget = new qrencodeWidget(image);

    widget->show();
    this->close();
}

void ShoppingCartUI::on_pushButtonReturn_clicked()
{
    MainForm *widget = new MainForm;
    widget->show();
    this->close();
}
