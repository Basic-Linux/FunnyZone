#include "drinktypemenuui.h"
#include "ui_drinktypemenuui.h"

DrinkTypeMenuUI::DrinkTypeMenuUI(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrinkTypeMenuUI)
{
    ui->setupUi(this);
    pix = new QPixmap(BACKGROUND_URL);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->ginfo.GStyle = name;
    ui->pushButton->setText(name);

    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));
}

DrinkTypeMenuUI::~DrinkTypeMenuUI()
{
    delete ui;
}

void DrinkTypeMenuUI::on_pushButton_clicked()
{
    QJsonObject obj;
    emit sigUI2Console(10,ginfo,obj);
    obj.insert(TYPE,ginfo.GStyle);
    emit sigUI2Console(1,ginfo,obj);
}

void DrinkTypeMenuUI::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),*pix);
}
