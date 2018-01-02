#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T22:30:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlite3-example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlite3.cpp

HEADERS  += mainwindow.h \
    sqlite3.h

FORMS    += mainwindow.ui
