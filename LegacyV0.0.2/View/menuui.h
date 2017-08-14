#ifndef MENUUI_H
#define MENUUI_H

#include <QWidget>
#include <QPushButton>

#include "stuff.h"
#include "menuwidget.h"
#include "ui_menuui.h"
#include "selfdef.h"
#include "drinktypemenuui.h"

namespace Ui {
class MenuUI;
}

class MenuUI : public QWidget
{
    Q_OBJECT

public:
    explicit MenuUI(QWidget *parent = 0);
    ~MenuUI();

    void setMenuType(MenuType type){
        this->menuType = type;
        if(this->menuType == ListMenu)
            ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout);
        else if(this->menuType == GridMenu)
            ui->scrollAreaWidgetContents->setLayout(new QGridLayout);
        else if(this->menuType == ShoppMenu)
            ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout);
    }
    //向其中添加元素
    void addElement(GInfo ginfo);

    QLayout * getLayout(){
        return ui->scrollAreaWidgetContents->layout();
    }

    //清除之前的layout中的控件(一般用于选用不同的饮料按钮)
    void removePreWidgets(){
        QLayout *layout = ui->scrollAreaWidgetContents->layout();
        delete layout;
        setMenuType(this->menuType);
    }
private:
    Ui::MenuUI *ui;
    MenuType menuType;
    int Maxcolumn;
    int Maxrow;
};

#endif // MENUUI_H
