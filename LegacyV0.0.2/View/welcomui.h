#ifndef WELCOMUI_H
#define WELCOMUI_H

#include <QWidget>
#include <QPainter>

#include "advertisementui.h"
#include "mainform.h"

namespace Ui {
class WelcomUI;
}

class WelcomUI : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomUI(QWidget *parent = 0);
    ~WelcomUI();

private slots:
    //做收尾工作
    void closeEvent(QCloseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

//    void on_pushButton_4_clicked();

//    void on_pushButton_5_clicked();

private:
    Ui::WelcomUI *ui;
};

#endif // WELCOMUI_H
