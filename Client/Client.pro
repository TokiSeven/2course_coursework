#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T01:40:10
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    launcher.cpp \
    container.cpp \
    game_net.cpp \
    ../Server/player.cpp

HEADERS  += mainwindow.h \
    form.h \
    launcher.h \
    container.h \
    game_net.h \
    ../Server/player.h

FORMS    += mainwindow.ui
