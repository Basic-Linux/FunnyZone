#ifndef THREEWIDGET_H
#define THREEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#define PIXSIZE QSize(50,50)
namespace Ui {
class threeWidget;
}

class threeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit threeWidget(QWidget *parent = 0);
    ~threeWidget();
    void initThreeWidget();
    void printLabel(QString file,QLabel *widget);
    void printLinetext(QLineEdit *widget);
signals:
    void clicked(QWidget *);
protected:
    void mousePressEvent(QMouseEvent * event);
public:
    Ui::threeWidget *ui;
};

#endif // THREEWIDGET_H
