TARGET = SmartAPP
TEMPLATE = app

QT += core widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += c++14

include($$PWD/controlWidget/controlWidget.pri)
include($$PWD/loginWidget/loginWidget.pri)
include($$PWD/tcpClient/tcpClient.pri)
include($$PWD/jason/jason.pri)
SOURCES += \
    main.cpp \
    loginui.cpp \
    controlModule.cpp \
    consoleui.cpp \
    def_const.cpp

FORMS += \
    contwidget.ui \
    loginui.ui \
    consoleui.ui

HEADERS += \
    def_const.h \
    loginui.h \
    controlModule.h \
    consoleui.h

RESOURCES += \
    interfaceres.qrc
