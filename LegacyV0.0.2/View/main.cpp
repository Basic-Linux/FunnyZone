#include "welcomui.h"
#include <QApplication>
#include "console.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Console::getConsoleInstance()->setSkin();
    WelcomUI w;
    w.show();

    return a.exec();
}
