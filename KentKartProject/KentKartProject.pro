#-------------------------------------------------
#
# Project created by QtCreator 2020-07-17T13:41:01
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += core
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KentKartProject
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           secwindow.cpp

HEADERS  += mainwindow.h \
            secwindow.h

FORMS    += mainwindow.ui \
            secwindow.ui

DISTFILES += \
    KenkKartQMl.qml
