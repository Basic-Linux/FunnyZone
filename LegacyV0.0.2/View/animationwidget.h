#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

namespace Ui {
class AnimationWidget;
}

class AnimationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationWidget(QWidget *parent = 0);
    ~AnimationWidget();

    void setPixmap(QString url){
        this->pix.load(url);
        update();
    }

    void clacSize()
    {
        r_w = (pix.width() * 1.0) / (this->width() * 1.0) ;
        r_h = (pix.height() * 1.0) / (this->height() * 1.0) ;
        if(r_w > 1 || r_h > 1)
        {
            if(r_w > r_h)
            {
                r_w = (this->width() * 1.0) / (pix.width() * 1.0);
                r_h = r_w;
            }
            else
            {
                r_h = (this->height() * 1.0) / (pix.height() * 1.0);
                r_w = r_h;
            }

        }
        else
        {
            r_w = 1;
            r_h = 1;
        }
        update();
    }

private:
    void paintEvent(QPaintEvent *event);

private:
    Ui::AnimationWidget *ui;
    QPixmap pix;
    float r_w;
    float r_h;
};

#endif // ANIMATIONWIDGET_H
