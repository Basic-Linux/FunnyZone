#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(struct GInfo &ginfo,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->ginfo = ginfo;

    connect(this,SIGNAL(sigUI2Console(int,GInfo,QJsonObject)),
            Console::getConsoleInstance(),SLOT(slotUI2Console(int,GInfo,QJsonObject)));

    timerInit.setSingleShot(true);
    connect(&timerInit,SIGNAL(timeout()),this,SLOT(slotTimeOutInit()));
    timerInit.start(0.1);
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

QString MenuWidget::getGName()
{
    return ginfo.GName;
}

GInfo MenuWidget::getGinfo()
{
    return this->ginfo;
}

void MenuWidget::addGcount()
{
    ui->spinBox->setValue(ui->spinBox->value() + 1);
}

void MenuWidget::on_spinBox_valueChanged(const QString &arg1)
{
    this->ginfo.UserGCount = ui->spinBox->value();
//    emit sigMenuChanged();
    QString str = QString::asprintf("%3.1f * %d",ginfo.GPrice,ui->spinBox->value());
//    ui->lineEdit_sum->setText(str);
    QJsonObject obj;
    emit sigUI2Console(7,ginfo,obj);

    if(this->ginfo.UserGCount <= 0)
        this->close();

    DBUG_OUT;
}

void MenuWidget::slotTimeOutInit()
{
    qDebug() << ui->widget_pic->size();
    pix.load(ginfo.GPicURL);

//    pix = pix.scaled(i->widget_pic->size());

    ui->widget_pic->setPixmap(ginfo.GPicURL);
    ui->lineEdit_name->setText(ginfo.GName);
//    ui->lineEdit_price->setText( QString::asprintf("%3.1f",ginfo.GPrice) );
    ui->label_price_->setText( QString::asprintf("%3.1f",ginfo.GPrice) );
    QString str = QString::asprintf("%3.1f * %d",ginfo.GPrice,ui->spinBox->value());
//    ui->lineEdit_sum->setText(str);
    ui->spinBox->setValue(ginfo.UserGCount);
}
