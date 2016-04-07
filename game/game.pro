#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T22:34:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        launcher.cpp \
    container.cpp \
    game_graphic.cpp \
    game_net.cpp \
    launcher_connect.cpp \
    mainwindow_connect.cpp \
    player.cpp \
    server.cpp

HEADERS  += launcher.h \
    container.h \
    game_graphic.h \
    game_net.h \
    launcher_connect.h \
    mainwindow_connect.h \
    player.h \
    server.h

FORMS    += launcher.ui \
    mainwindow_connect.ui

DISTFILES += \
    game.pro.user


LIBS += -LD:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:/SFML/include
DEPENDPATH += D:/SFML/include
