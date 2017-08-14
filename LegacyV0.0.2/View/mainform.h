#ifndef MAINFORM_H
#define MAINFORM_H
/*
 * 整体执行流程
 * 1 进入页面的时候一立即向SQL请求有多少种饮料
 * 2 根据返回的数据列举出menu，并默认点击第一个界面
 * 3 发送请求这一种饮料的请求，根据接收到数据 list中显示出各个饮料的数据
*/
#include <QWidget>

#include "Console/head/console.h"
#include "welcomui.h"
#include "shoppingcartui.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

    Ui::MainForm * getMainFormUIPoint(){
        return this->ui;
    }

private slots:
    void slotConsole2UI(int sigCode,GInfo ginfo,QJsonObject obj);

    void on_pushButton_Back_clicked();

    void on_pushButton_calc_clicked();

signals:
    void sigUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
