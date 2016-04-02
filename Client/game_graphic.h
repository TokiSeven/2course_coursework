#ifndef GAME_GRAPHIC_H
#define GAME_GRAPHIC_H

//qt libraries
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

//personal libraries
#include "container.h"

//sfml libraries
#include <SFML/Graphics.hpp>

class Game_graphic : public QObject
{
    Q_OBJECT

public:
    Game_graphic(Container *cont);
    ~Game_graphic();

    void game_start();

signals:
    void signal_update();

public slots:
    void slot_position(Player);
    void slot_update();

protected:
    //sfml
    void initialization();
    void main_cycle();
    void events(sf::Event&);
    void draw();
    sf::RenderWindow *window;

    //db
    Container *cont;
    QList<sf::RectangleShape> pl_all;
    sf::RectangleShape pl_current;

    //for window
    int windowHeight;
    int windowWidth;
    QString windowName;
};

#endif // GAME_GRAPHIC_H
