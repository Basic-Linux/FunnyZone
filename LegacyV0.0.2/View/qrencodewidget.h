#ifndef QRENCODEWIDGET_H
#define QRENCODEWIDGET_H

#include <QWidget>
#include "selfdef.h"
#include "console.h"
#include "mainform.h"

namespace Ui {
class qrencodeWidget;
}

class qrencodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit qrencodeWidget(QWidget *parent = 0);
    explicit qrencodeWidget(QImage image,QWidget *parent = 0);
    ~qrencodeWidget();

    void setRencode(QImage &pic);
    void showPaySucess();

private slots:
    void on_pushButton_clicked();

    void slotConsole2UI(int sigCode,GInfo ginfo,QJsonObject obj);

signals:
    void sigUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);

private:
    Ui::qrencodeWidget *ui;
    QPixmap pix;
    QTimer timer;
};

#endif // QRENCODEWIDGET_H
