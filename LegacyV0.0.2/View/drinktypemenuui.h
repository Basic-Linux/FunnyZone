#ifndef DRINKTYPEMENUUI_H
#define DRINKTYPEMENUUI_H

#include <QWidget>

#include "selfdef.h"
#include "console.h"

namespace Ui {
class DrinkTypeMenuUI;
}

class DrinkTypeMenuUI : public QWidget
{
    Q_OBJECT

public:
    explicit DrinkTypeMenuUI(QString name,QWidget *parent = 0);
    ~DrinkTypeMenuUI();

private slots:
    void on_pushButton_clicked();

    void paintEvent(QPaintEvent *event);

signals:
    void sigUI2Console(int sigCode,GInfo ginfo,QJsonObject obj);

private:
    Ui::DrinkTypeMenuUI *ui;
    GInfo ginfo;
    QPixmap *pix;
};

#endif // DRINKTYPEMENUUI_H
