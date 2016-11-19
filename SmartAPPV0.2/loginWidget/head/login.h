#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#define LOGINSIZE QSize(800,600)
#define PIXSIZE QSize(50,50)
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    void initLogin();
    Ui::login *ui;
protected:
    void paintBackground(QImage *pixmap);
    void paintEdittext(QPixmap *pixmap,QWidget *widget);
    void paintLabel(QPixmap *pixmap,QLabel *widget);
    void paintBtn(QPixmap *pixmap,QPushButton *widget);
    void paintEvent(QPaintEvent *);
private:

    QImage *image;
    QPixmap*  edittext;
    QPixmap*  labelico_account;
    QPixmap*  labelico_password;
    QPixmap*  btn_login;
    QPixmap*  btn_exit;
};

#endif // LOGIN_H
