#ifndef API_H
#define API_H

#include <QObject>
#include "container.h"
#include "game_net.h"
#include "game_graphic.h"
#include "mainwindow_connect.h"
#include <QThread>

class API
        : public QObject
{
    Q_OBJECT
public:
    explicit API(QObject *parent = 0);
    ~API();

    //start game, if setPlName & connection to server was made successfully
    void startGame();

    inline Game_net* getGameNetwork()const{return this->game_net;}
    inline Game_graphic* getGameGraphics()const{return this->game_graph;}
    inline Container* getGameContainer()const{return this->cont;}
    inline MainWindow_connect* getMainWindow()const{return this->mw;}
signals:

private slots:
    void slot_startGame();
    void slot_gameClose();

protected:
    //for data
    void connect_Game_net();
    void connect_Game_graphic();
    void connect_Container();
    void connect_MainWindow_connect();
    void connect_Player_Current();
    void connect_all();

    //for game too
    bool isGame;

    //for game
    Game_net *game_net;
    Game_graphic *game_graph;
    Container *cont;
    MainWindow_connect *mw;
    //bools for game
    bool isGameNet, isGameGraph, isContainer, isMainWindow;
};

#endif // API_H
