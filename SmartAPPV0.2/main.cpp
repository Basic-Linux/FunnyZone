/*
 *SmartAPP项目说明文档：
 * 项目目的：1 功能：通过C/S架构实现网络通讯，并且能够解析指定数据包
 *          2 UI：仿照某成品智能家居UI来设计
 * 工程框架：1 API封装需求：对于系统API，再次封装的话需要在程序最后加上debug信息；对于自己写的API，采用简单工厂模式
 *          2 工程分三个模块。（1）view模块 模块包括selfUI；
 *                                      control模块的指针；
 *                          （2）control模块 模块包括selfcontrol:a.打包/解包 发送/接受
 *                                           model模块的指针；
 *                          （3）model模块 模块包括selfmodel:a.数据存放 更新UI
 *                                         view模块的指针；
 *             模块间通讯机制：view --- control 信号 槽
 *                           control -- model 消息队列
 *                           model -- view 消息队列
 *
 *
*/

#include <QApplication>
#include "loginui.h"
#include "consoleui.h"
#include "controlModule.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controlModule controlmodule;
    loginUI w(&controlmodule);
    w.show();

    return a.exec();
}

