#ifndef API_H
#define API_H

#include <QObject>
#include "container.h"
#include "game_net.h"
#include "game_graphic.h"
#include <QThread>

class API : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = 0);

    void startGame();//start game, if setPlName & connect to server was been

    inline Game_net* getGameNetwork()const{return this->game_net;}
    inline Game_graphic* getGameGraphics()const{return this->game_graph;}
    inline Container* getGameContainer()const{return this->cont;}
signals:

public slots:

private:
    //for game
    Game_net *game_net;
    Game_graphic *game_graph;
    Container *cont;
};

#endif // API_H
