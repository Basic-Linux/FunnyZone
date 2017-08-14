#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QMetaType>
#include "SelfDEF.h"
#include "console.h"

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(struct GInfo &ginfo,QWidget *parent = 0);
    ~MenuWidget();

//实时监测订单栏位的变动
signals:
    void sigMenuChanged();
    void sigUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);

private slots:
    void on_spinBox_valueChanged(const QString &arg1);

    void slotTimeOutInit();
public:
    //logic
    QString getGName();

    GInfo getGinfo();

    void addGcount();

private:
    Ui::MenuWidget *ui;
    struct GInfo ginfo;
    QPixmap pix;

    QTimer timerInit;
};

#endif // MENUWIDGET_H
