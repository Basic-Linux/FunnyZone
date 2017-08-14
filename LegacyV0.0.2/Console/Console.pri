#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T14:21:03
#
#-------------------------------------------------
QT       += core gui serialport

include($$PWD/QRencode/QRencode.pri)

INCLUDEPATH += $$PWD/head/
INCLUDEPATH += $$PWD/../View/
INCLUDEPATH += $$PWD/../Module/

HEADERS += \
    $$PWD/head/*.h

SOURCES += \
    $$PWD/cpp/*.cpp
