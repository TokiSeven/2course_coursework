#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T01:19:17
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server_v01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    client.h \
    player.h

FORMS    += mainwindow.ui
