#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T10:42:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newDJ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qextserialenumerator.cpp \
    posix_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    tcpclientsocket.cpp

HEADERS  += mainwindow.h \
    qextserialport.h \
    qextserialenumerator.h \
    qextserialbase.h \
    posix_qextserialport.h \
    tcpclientsocket.h

FORMS    += mainwindow.ui

unix:DEFINES           += _TTY_POSIX_

TRANSLATIONS  = tcpserver_zh.ts

QT += network
