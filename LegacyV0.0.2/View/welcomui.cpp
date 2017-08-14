#include "welcomui.h"
#include "ui_welcomui.h"

WelcomUI::WelcomUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
//    Console::getConsoleInstance()->setScreenSize(this);
//    this->move(0,0);

    this->showFullScreen();

    //开启video广告
    ui->widget_Video->addVideo("C:/Users/a3299/Desktop/tmp/LegacyV0.0.2/test/David Guetta,Justin Bieber - 2U.mp4");
    ui->widget_Video->addVideo("C:/Users/a3299/Desktop/tmp/LegacyV0.0.2/test/J.Fla - The Greatest.mp4");
    ui->widget_Video->playVideo(true);
    //开启图片广告
    ui->widget_ADPicture->addADList(":/ad1.jpg");
    ui->widget_ADPicture->addADList(":/ad2.jpg");
    ui->widget_ADPicture->setSpeed(0.2);
    ui->widget_ADPicture->setADType(PictureAD);
    ui->widget_ADPicture->playAD(true);
    //开启文字广告
    ui->widget_ADText->setSpeed(0.01);
    ui->widget_ADText->setADType(TextAD);
    ui->widget_ADText->addADList("华清远见智能售货机 如需要购买请点击屏幕");
    ui->widget_ADText->playAD(true);
    qDebug() << "ADContant = ";
}

WelcomUI::~WelcomUI()
{
    delete ui;
}
//实验发现video组件不会关闭
void WelcomUI::closeEvent(QCloseEvent *event)
{
    ui->widget_Video->close();
}

void WelcomUI::mouseReleaseEvent(QMouseEvent *event)
{
    MainForm *form = new MainForm;
    form->show();
    this->close();
}

//void WelcomUI::on_pushButton_clicked()
//{
//    ui->widget_ADPicture->addADList(":/ad1.jpg");
//    ui->widget_ADPicture->addADList(":/ad2.jpg");
//    ui->widget_ADPicture->setSpeed(0.2);
//    ui->widget_ADPicture->setADType(PictureAD);
//    ui->widget_ADPicture->playAD(true);
//}

//void WelcomUI::on_pushButton_2_clicked()
//{
//    ui->widget_ADText->setSpeed(0.01);
//    ui->widget_ADText->setADType(TextAD);
//    ui->widget_ADText->addADList("华清远见");
//    ui->widget_ADText->addADList("321");
//    ui->widget_ADText->addADList("789");
//    ui->widget_ADText->playAD(true);
//}

//void WelcomUI::on_pushButton_3_clicked()
//{
//    ui->widget_Video->addVideo("C:/Users/a3299/Desktop/tmp/Legacy/test/David Guetta,Justin Bieber - 2U.mp4");
//    ui->widget_Video->addVideo("C:/Users/a3299/Desktop/tmp/Legacy/test/J.Fla - The Greatest.mp4");
//    ui->widget_Video->playVideo(true);
//}

//void WelcomUI::on_pushButton_4_clicked()
//{
//    ui->widget_Video->playNext();
//}

//void WelcomUI::on_pushButton_5_clicked()
//{
//    MainForm *form = new MainForm;
//    form->show();
//    this->close();
//}
