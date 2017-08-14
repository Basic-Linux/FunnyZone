#ifndef VIDEOADUI_H
#define VIDEOADUI_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioRecorder>
#include <QVideoWidget>
#include "ui_videoadui.h"

#include "selfdef.h"

namespace Ui {
class VideoADUI;
}

class VideoADUI : public QWidget
{
    Q_OBJECT

public:
    explicit VideoADUI(QWidget *parent = 0);
    ~VideoADUI();

    void playVideo(bool flag){
        if(flag)
            player->play();
        else
            player->pause();
    }

    void addVideo(QString url){
        QMediaContent *media = new QMediaContent(QUrl::fromLocalFile(url));
        media->canonicalResource().setResolution(ui->widget_Video->size());
        playlist->addMedia(*media);
    }

    void removeVideo(int index){
        player->pause();
        playlist->removeMedia(index);
        player->play();
    }

    void playNext(){
        player->stop();
        playlist->setCurrentIndex(playlist->nextIndex());
        player->play();
    }

private slots:
    void closeEvent(QCloseEvent *event);

private:
    Ui::VideoADUI *ui;
    QMediaPlayer * player;
    QMediaPlaylist * playlist;
};

#endif // VIDEOADUI_H
