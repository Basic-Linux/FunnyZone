#include "threeWidget.h"
#include "ui_threeWidget.h"

threeWidget::threeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::threeWidget)
{
    ui->setupUi(this);
    initThreeWidget();
}

threeWidget::~threeWidget()
{
    delete ui;
}
void threeWidget::initThreeWidget()
{
    printLabel(":/res/illumination_button_ico.png",ui->label_light);
    printLabel(":/res/humidity_ico.png",ui->label_temp);
    printLabel(":/res/temperature_button_ico.png",ui->label_hum);
    printLinetext(ui->lineEdit_light);
    printLinetext(ui->lineEdit_temp);
    printLinetext(ui->lineEdit_hum);
    ui->lineEdit_light->setAttribute(Qt::WA_TranslucentBackground);
}
void threeWidget::printLinetext(QLineEdit *widget)
{
    widget->setFrame(false);
    QPalette palette;
    palette.setColor(widget->backgroundRole(),QColor(255,255,255,0));
    widget->setPalette(palette);
}
void threeWidget::printLabel(QString file,QLabel *widget)
{
    QPixmap pixmap(file);
    pixmap = pixmap.scaled(PIXSIZE);
    widget->setPixmap(pixmap);
}
void threeWidget::mousePressEvent(QMouseEvent * event)
{
    emit clicked(this);
}
