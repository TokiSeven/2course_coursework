#ifndef GAME_GRAPHIC_H
#define GAME_GRAPHIC_H

#include <QObject>
#include <QTimer>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <QThread>
#include "container.h"
//from game.h
#include <vector>
#include <list>
#include "level.h"
#include "animation.h"
#include "entity.h"
#include "spell.h"
#include "player.h"
#include "healthbar.h"

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

    //from game.h
    View *view;
    Level lvl; // карта
    Texture ichigo_t, bg; // текстуры
    AnimationManager anim; // анимации персонажа
    AnimationManager anim2; // анимации способности
    Sprite background; // фон
    std::list<Entity*>  entities; // массив объектов
    std::list<Entity*>::iterator it;
    PLAYER *Ichigo; // игрок
    HealthBar healthBar; // полоска жизней
    Music music;
    bool o;
    bool space; // проверка одного нажатия
    Clock clock; // часы
};

#endif // GAME_GRAPHIC_H
