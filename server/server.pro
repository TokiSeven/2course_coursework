QT += core network
QT -= gui

CONFIG += c++11

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    ../game/player.cpp \
    network_main.cpp

HEADERS += \
    server.h \
    ../game/player.h \
    network_main.h
