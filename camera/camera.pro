#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T09:05:09
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = camera
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ffmpeg.cpp \
    largemotor.cpp \
    drawpanel.cpp \
    motorpath.cpp \
    cruisetask.cpp \
    ele_mach.cpp \
    zmqclient.cpp \
    robot_active_thread.cpp \
    qcustomplot.cpp \
    paintlabel.cpp \
    zmqserver.cpp

INCLUDEPATH += "../"
INCLUDEPATH += "./"

HEADERS  += mainwindow.h \
    ffmpeg.h \
    largemotor.h \
    drawpanel.h \
    motorpath.h \
    cruisetask.h \
    ele_mach.h \
    common.h \
    zmqclient.h \
    robot_active_thread.h \
    qcustomplot.h \
    paintlabel.h \
    zmqserver.h

FORMS    += mainwindow.ui
QT += network
LIBS    += -lavfilter \
#    ../motor/motor.o \
    -lavcodec \
    -lavformat \
    -lswscale \
    -lavutil \
    -lswresample \
#    -lnvdc_sdk \
#    -lIOTCAPIs \
#    -lAVAPIs \
    -lpthread \
    -lrt    \
    -lzmq

DISTFILES +=

RESOURCES += \
    qss.qrc
