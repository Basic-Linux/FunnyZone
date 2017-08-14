#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T09:43:07
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Legacy
TEMPLATE = app


include($$PWD/View/View.pri)
include($$PWD/Console/Console.pri)
include($$PWD/Module/Module.pri)
