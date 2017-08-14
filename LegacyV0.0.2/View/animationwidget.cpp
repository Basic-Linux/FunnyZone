#include "animationwidget.h"
#include "ui_animationwidget.h"

AnimationWidget::AnimationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

AnimationWidget::~AnimationWidget()
{
    delete ui;
}

void AnimationWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    clacSize();
    p.translate(this->width() / 2,this->height() / 2);
    p.drawPixmap( - pix.width() * r_w / 2,- pix.height()* r_h / 2,
                 pix.width() * r_w,pix.height()* r_h,pix);
}
