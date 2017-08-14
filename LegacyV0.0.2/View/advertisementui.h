#ifndef ADVERTISEMENTUI_H
#define ADVERTISEMENTUI_H
/*bref:
 * 使用本类需要做如下事情：
 * 1 设置广告类型
 * 2 添加广告源
 * 3 开启广告滚动
 * （4 期间可以控制广告滚动速度，和停留速度）
 */

#include <QWidget>
#include <QPainter>
#include <QTimer>

#include "selfdef.h"

namespace Ui {
class AdvertisementUI;
}

class AdvertisementUI : public QWidget
{
    Q_OBJECT

public:
    explicit AdvertisementUI(QWidget *parent = 0);
    ~AdvertisementUI();
    //设置播放广告的类型
    void setADType(ADType type){ this->adType = type;}
    //是否播放广告
    void playAD(bool flag){
        flagPlay = flag;
        if(flag){ timerAd.start(INTERVAL_AD);}
        else{timerAd.stop();}
    }

    void setSpeed(float perSpeed){
        if(perSpeed <= 1 && perSpeed > 0)
            this->speedAD = this->width() * perSpeed;
    }

    void setPauseTime(int time){ this->pauseAD = time; }

    void addADList(QString url){

        ADList.append(url);
        if(this->adType == PictureAD)
        {
            ADPictureList.append(new QPixmap(url));
        }
        else if(this->adType == TextAD)
        {
            ADContant.clear();
            for(int i = 0; i < ADList.count();i++)
            {
                ADContant.append(ADList.at(i));
                ADContant.append("    ");
            }
        }
    }

    void clearADList(){
        ADList.clear();
        for(int i = 0; i < ADPictureList.count();i++)
            delete ADPictureList.at(i);
        ADPictureList.clear();
    }

private slots:
    void paintEvent(QPaintEvent *event);

    void slotTimeOut();

private:
    Ui::AdvertisementUI *ui;
    //我们为了保证所有原数据完成，所有坚持保留这个list(不管是什么类型的广告)
    QList<QString> ADList;
    QList<QPixmap*> ADPictureList;
    ADType adType;
    bool flagPlay;
    //一些播放机制
    int speedAD;
    int pauseAD;
    int curFirstAD;
    int curSecondAD;
    QString ADContant;
    QPixmap background;
    int cPP;//(curPaintPosition)
    //一些播放需要的工具
    QTimer timerAd;
    QTimer timerAdPause;
};

#endif // ADVERTISEMENTUI_H
