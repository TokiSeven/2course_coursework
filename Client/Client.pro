#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T01:40:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    launcher.cpp \
    container.cpp \
    game_net.cpp \
    ../Server/player.cpp \
    game_graphic.cpp

HEADERS  += mainwindow.h \
    launcher.h \
    container.h \
    game_net.h \
    ../Server/player.h \
    game_graphic.h

FORMS    += mainwindow.ui


LIBS += -LD:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:/SFML/include
DEPENDPATH += D:/SFML/include
