#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T01:19:17
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    player.h \
    server.h

FORMS    += mainwindow.ui
