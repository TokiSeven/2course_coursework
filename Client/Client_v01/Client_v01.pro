#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T01:40:10
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client_v01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    launcher.cpp \
    container.cpp \
    game_net.cpp \
    ../../Server/Server_v01/player.cpp

HEADERS  += mainwindow.h \
    form.h \
    launcher.h \
    container.h \
    game_net.h \
    ../../Server/Server_v01/player.h

FORMS    += mainwindow.ui
