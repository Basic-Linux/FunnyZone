#include "advertisementui.h"
#include "ui_advertisementui.h"

AdvertisementUI::AdvertisementUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvertisementUI)
{
    ui->setupUi(this);
    flagPlay = true;
    adType = PictureAD;
    background.load(":/image/common/background.png");
    connect(&timerAd,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
    timerAdPause.setSingleShot(true);

    connect(&timerAdPause,&QTimer::timeout,[=](){
        if(!this->flagPlay)
            return ;
        else
            timerAd.start(INTERVAL_AD);
    });
    cPP = 0;

    setSpeed(SPEED_AD);
    setPauseTime(INTERVAL_ADPause);
}

AdvertisementUI::~AdvertisementUI()
{
    delete ui;
    this->timerAd.stop();
    this->timerAdPause.stop();
}

void AdvertisementUI::paintEvent(QPaintEvent *event)
{
    if(adType == PictureAD)
    {
        QPainter p(this);
        //防呆处理
        if(ADPictureList.count() == 0)
            return ;
        if(curFirstAD > ADPictureList.count() - 1)
        {
            curFirstAD = 0;
        }
        curSecondAD = curFirstAD + 1;
        if(curSecondAD > ADPictureList.count() - 1)
        {
            curSecondAD = 0;
        }
//        qDebug() << "pic count =" << curFirstAD << curSecondAD;
//        qDebug() << "piclist count =" << ADPictureList.count();
        p.drawPixmap(-cPP,0,
                     this->width(),this->height(),
                     *ADPictureList.at(curFirstAD));
        p.drawPixmap(this->width() - cPP,0,
                     this->width(),this->height(),
                     *ADPictureList.at(curSecondAD));
    }
    else if(adType == TextAD)
    {
        QPainter p(this);
//        if(ADList.count() == 0)
//            qDebug() << "ADList is empty";
//        p.drawPixmap(0,0,this->width(),this->height(),background);
        p.setPen(Qt::white);
        p.setFont(QFont (FONT_Family, FONT_SIZE,QFont::Bold));
        if(!ADContant.isEmpty())
            p.drawText(QRect(this->width() - cPP,this->height()/2,this->width(),this->height()),ADContant);
    }
    return QWidget::paintEvent(event);
}

void AdvertisementUI::slotTimeOut()
{
    if(adType == PictureAD)
    {
        cPP += speedAD;
        if(cPP >= this->width())
        {
            timerAd.stop();
            timerAdPause.start(INTERVAL_ADPause);
            curFirstAD ++;
            qDebug() << "fisr id changed" << curFirstAD;
            cPP = 0;
        }
    }
    else if(adType == TextAD)
    {
        cPP += speedAD;
        if(cPP >= this->width())
        {
            cPP = 0;
        }
    }


    update();
//    repaint();
}
