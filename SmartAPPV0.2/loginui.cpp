#include "loginui.h"
#include "ui_loginui.h"
#include "ui_login.h"
#include "consoleui.h"
#include <QImage>

loginUI::loginUI(controlModule *wh_control,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginUI),
    loginwidget(new login())
{
    //UI
    ui->setupUi(this);
    loginLayout = new QHBoxLayout();
    loginLayout->addWidget(loginwidget);
    loginLayout->setContentsMargins(0,0,0,0);
    this->setLayout(loginLayout);
    setWindowFlags(Qt::FramelessWindowHint);
    dragPos = new QPoint();
    this->wh_control = wh_control;
    connect(loginwidget->ui->login_btn,SIGNAL(clicked()),this,SLOT(loginDataSend()));
    connect(loginwidget->ui->exit_btn,SIGNAL(clicked()),this,SLOT(close()));
    connect(wh_control,SIGNAL(sigDataRecved(uint8_t,QJsonObject)),this,SLOT(loginDataRecved(uint8_t,QJsonObject)));
}

loginUI::~loginUI()
{
    delete ui;
}
void loginUI::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton)
    {
        *dragPos = e->globalPos() - frameGeometry().topLeft();
        e->accept();
    }
}
void loginUI::mouseMoveEvent(QMouseEvent * e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - *dragPos);
        e->accept();
    }
}
void loginUI::loginDataSend()
{
    QJsonObject json_object;
    json_object.insert(J_userName,loginwidget->ui->account_edit->text().toStdString().c_str());
    json_object.insert(J_password,loginwidget->ui->password_edit->text().toStdString().c_str());
    json_object.insert("isHavePassword:","false");
    wh_control->socketdataSend(LOGIN,json_object);

}

void loginUI::loginDataRecved(uint8_t taskID,QJsonObject json_object)
{
    consoleUI *console;
    switch (taskID) {
    case LOGIN:
        userToken = json_object.take(J_userToken).toString();
        if(userToken == QJsonValue(QJsonValue::Undefined).toString())
        {
            QMessageBox::warning(0,tr("网络包错误"),tr("未找到userToken"));
        }
        else if((userToken == "null")  && ( (json_object.take(J_stateCode).toInt() == 2)
                ||  (json_object.take(J_stateCode).toInt() == 3)  ))
        {
            QMessageBox::warning(0,tr("信息错误"),tr("账号密码错误"));
        }
        qDebug() << "userTOken = " << userToken;
        console  = new consoleUI(wh_control,0);
        console->show();
        this->close();
        return ;
    default:
        break;
    }
    DBUG_OUT;
}
void loginUI::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    painter.fillRect(0,0,backgroundPixmap->width(),backgroundPixmap->height(),*backgroundPixmap);
}
