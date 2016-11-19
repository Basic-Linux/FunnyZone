#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    initLogin();
    //优化editText
    //connect(ui->account_edit,SIGNAL(editingFinished()),this,SLOT(paintEdittext(edittext,ui->account_edit);));
    //connect(ui->password_edit,SIGNAL(editingFinished()),this,SLOT(paintEdittext(edittext,ui->password_edit);));

}
login::~login()
{
    delete ui;
    delete image;
    delete edittext;
    delete labelico_account;
    delete labelico_password;
    delete btn_login;
    delete btn_exit;
}
void login::initLogin()
{
    resize(LOGINSIZE);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    image = new QImage(":/res/background.jpg");

    edittext = new QPixmap(":/res/edit.png");

    labelico_account = new QPixmap(":/res/account_ico.png");

    labelico_password = new QPixmap(":/res/password_ico.png");
    btn_login = new QPixmap(":/res/btnLoginIn.png");
    btn_exit = new QPixmap(":/res/exit.png");
    update();
}
void login::paintBackground(QImage *pixmap)
{
    *image = image->scaled(LOGINSIZE);
    QPainter painter(this);
    painter.fillRect(0,0,this->width(),this->height(),*pixmap);
}
void login::paintEdittext(QPixmap *pixmap,QWidget *widget)
{
    QPalette palette;
    palette.setBrush(widget->backgroundRole(),QBrush(*pixmap));
    widget->setPalette(palette);
}
void login::paintLabel(QPixmap *pixmap,QLabel *widget)
{
    *pixmap = pixmap->scaled(PIXSIZE);
    widget->setPixmap(*pixmap);
}
void login::paintBtn(QPixmap *pixmap,QPushButton *widget)
{
    *pixmap = pixmap->scaled(PIXSIZE);
    widget->setIcon(*pixmap);
}
void login::paintEvent(QPaintEvent *)
{
    paintBackground(image);
//    paintEdittext(edittext,ui->account_edit);
//    paintEdittext(edittext,ui->password_edit);
    paintLabel(labelico_account,ui->account_label);
    paintLabel(labelico_password,ui->password_label);
    paintBtn(btn_login,ui->login_btn);
    paintBtn(btn_exit,ui->exit_btn);
}
