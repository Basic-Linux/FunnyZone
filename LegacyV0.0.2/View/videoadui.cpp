#include "videoadui.h"
#include "ui_videoadui.h"

VideoADUI::VideoADUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoADUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //视频相关
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setVideoOutput(ui->widget_Video);
    player->setPlaylist(playlist);
}

VideoADUI::~VideoADUI()
{
    delete ui;

}

void VideoADUI::closeEvent(QCloseEvent *event)
{
    player->stop();
    player->deleteLater();
}
