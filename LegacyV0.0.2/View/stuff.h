#ifndef STUFF_H
#define STUFF_H

#include <QWidget>
#include "SelfDEF.h"
#include "console.h"

namespace Ui {
class Stuff;
}

class Stuff : public QWidget
{
    Q_OBJECT

public:
    explicit Stuff(struct GInfo &ginfo,QWidget *parent = 0);
    ~Stuff();
    //功能
    //1 设置货物图片
    void setPic(QString url);
    //2 获取货物名字
    QString getGName();
    //3 获取ginfo（等同于原本数据库的东西，慎用）
    GInfo& getGinfo();
    //4 发送购物信号
protected:
    //发送购买信号
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sigUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);

private:
    Ui::Stuff *ui;
    struct GInfo ginfo;
//    QTimer timerInit;
};

#endif // STUFF_H
