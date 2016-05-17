TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp

LIBS += -LD:\SFML\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:\SFML\include
DEPENDPATH += D:\SFML\include

HEADERS += \
    game.h \
    animation.h \
    player.h \
    spell.h \
    entity.h \
    level.h \
    healthbar.h

RESOURCES += \
    res.qrc
