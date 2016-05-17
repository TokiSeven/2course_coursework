#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T22:34:33
#
#-------------------------------------------------

QT       += core gui network

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
    container.cpp \
    game_graphic.cpp \
    game_net.cpp \
    mainwindow_connect.cpp \
    ../server/network_main.cpp \
    api.cpp \
    player_old.cpp \
    coursework/TinyXML/tinystr.cpp \
    coursework/TinyXML/tinyxml.cpp \
    coursework/TinyXML/tinyxmlerror.cpp \
    coursework/TinyXML/tinyxmlparser.cpp

HEADERS  += \
    container.h \
    game_graphic.h \
    game_net.h \
    mainwindow_connect.h \
    ../server/network_main.h \
    api.h \
    player_old.h \
    animation.h \
    entity.h \
    healthbar.h \
    level.h \
    player.h \
    spell.h \
    coursework/TinyXML/tinystr.h \
    coursework/TinyXML/tinyxml.h \
    coursework/animation.h \
    coursework/entity.h \
    coursework/game.h \
    coursework/healthbar.h \
    coursework/level.h \
    coursework/player.h \
    coursework/spell.h

FORMS    += \
    mainwindow_connect.ui

DISTFILES += \
    game.pro.user


LIBS += -LD:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:/SFML/include
DEPENDPATH += D:/SFML/include

RESOURCES += \
    launcher_images.qrc \
    coursework/res.qrc
