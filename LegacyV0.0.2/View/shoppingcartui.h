#ifndef SHOPPINGCARTUI_H
#define SHOPPINGCARTUI_H

#include <QWidget>
//#include <QList>

#include "selfdef.h"
#include "console.h"
#include "mainform.h"
#include "menuwidget.h"
#include "qrencodewidget.h"

namespace Ui {
class ShoppingCartUI;
}

class ShoppingCartUI : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCartUI(QWidget *parent = 0);
    ~ShoppingCartUI();

private slots:
    void slotConsole2UI(int sigCode,GInfo ginfo,QJsonObject obj);

    void on_pushButtonClear_clicked();

    void on_pushButtonReturn_clicked();

signals:
    void sigUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);

private:
    Ui::ShoppingCartUI *ui;
    //console总体资源的映射,但是这个映射中是有货物购买的数量的
    QList<GInfo> ShoppingCartList;
};

#endif // SHOPPINGCARTUI_H
