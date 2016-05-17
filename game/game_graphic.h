#ifndef GAME_GRAPHIC_H
#define GAME_GRAPHIC_H

#include <QObject>
#include <QTimer>
#include "container.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "coursework/game.h"

class Game_graphic : public QObject
{
    Q_OBJECT

public:
    Game_graphic(Container *cont, QObject *parent = 0);
    ~Game_graphic();

    void game_start();

signals:
    void signal_update();
    void signal_game_closed();

public slots:
    void slot_position(Player_old);
    void slot_update();
    void slot_game_start();
    void slot_close();

protected:
    //sfml
    void initialization();
    void updatePlayersAll();
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
