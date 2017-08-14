#include "menuui.h"
#include "ui_menuui.h"

MenuUI::MenuUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    menuType = ListMenu;
    Maxcolumn = 10 / (SIZE_LIST_W * 10);
//    Maxrow = 10 / (SIZE_LIST_H * 10);
    qDebug("Maxcolumn = %d;Mincolumn = %d,",Maxcolumn,Maxrow);
}

MenuUI::~MenuUI()
{
    delete ui;
}

void MenuUI::addElement(GInfo ginfo)
{
    if(this->menuType == ListMenu)
    {
        QVBoxLayout *layout = dynamic_cast<QVBoxLayout *>( ui->scrollAreaWidgetContents->layout() );
        DrinkTypeMenuUI *widget = new DrinkTypeMenuUI(ginfo.GStyle);
//        widget->setMaximumSize(this->width() * SIZE_MENU_W
//                               ,this->height() * SIZE_MENU_H);
        widget->setMaximumHeight(this->height() * SIZE_MENU_H);
//        widget->setMinimumSize(this->width() * SIZE_MENU_W
//                               ,this->height() * SIZE_MENU_H);
        layout->addWidget(widget);
    }
    else if(this->menuType == ShoppMenu)
    {
        QVBoxLayout *layout = dynamic_cast<QVBoxLayout *>( ui->scrollAreaWidgetContents->layout() );
        MenuWidget *widget = new MenuWidget(ginfo);
//        widget->setMaximumWidth(this->width() * SHOP_MENU_W);
        widget->setMaximumHeight(this->height() * SHOP_MENU_H);
        widget->setMinimumWidth(this->width() * SHOP_MENU_W);
//        widget->setMinimumSize(this->width() * SHOP_MENU_W
//                               ,this->height() * SHOP_MENU_H);
        layout->addWidget(widget);
    }
    else if(this->menuType == GridMenu)
    {
        QGridLayout *layout = dynamic_cast<QGridLayout *>( ui->scrollAreaWidgetContents->layout() );
//        qDebug() << "layout count = "<<layout->count();
        Stuff *widget = new Stuff(ginfo);
        widget->setMaximumSize(this->width() * SIZE_LIST_W
                               ,this->height() * SIZE_LIST_H);
        widget->setMinimumSize(this->width() * SIZE_LIST_W
                               ,this->height() * SIZE_LIST_H);
        if(layout->count() == 0)
            layout->addWidget(widget);
        else
        {
            //列，行
            int column = 0,row = 0;
            row = layout->count() / (Maxcolumn);
            column = ( layout->count() ) % Maxcolumn;
            qDebug("count = %d,row = %d,colum = %d",layout->count(),row,column);
            layout->addWidget(widget,row,column);
        }
    }
}
