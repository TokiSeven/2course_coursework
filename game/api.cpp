#include "api.h"

API::API(QObject *parent) : QObject(parent)
{
    this->mw = new MainWindow_connect();
    this->cont = new Container(QString("NoName"), QHostAddress("127.0.0.1"), 1100, 2200, (QObject*)this);
    this->game_net = new Game_net(cont, (QObject*)this);
    this->game_graph = new Game_graphic(cont);

    this->connect_all();
}

void API::startGame()
{
    //game_graph->game_start();
    //Create a thread for graphic part

    QThread *thread = new QThread;
    game_graph->moveToThread(thread);
    connect(thread, SIGNAL(started()), game_graph, SLOT(slot_game_start()));
    connect(game_graph, SIGNAL(signal_game_closed()), thread, SLOT(quit()));
    connect(game_graph, SIGNAL(signal_game_closed()), game_graph, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void API::slot_startGame()
{
    this->startGame();
}

void API::slot_gameClose()
{
    delete this->game_graph;
    delete this->game_net;
    delete this->mw;
    delete this->cont;

    this->deleteLater();
}

void API::connect_Game_net()
{
    connect(this->getGameNetwork(), SIGNAL(connected()), this->getMainWindow(), SLOT(answerTrue()));
    connect(this->getGameNetwork(), SIGNAL(connected()), this, SLOT(slot_startGame()));

    connect(this->getGameNetwork(), SIGNAL(disconnected()), this->getMainWindow(), SLOT(serverTimeout()));

    connect(this->getGameNetwork(), SIGNAL(nick_incorrect()), this->getMainWindow(), SLOT(answerFalse()));

    connect(this->getGameNetwork(), SIGNAL(signal_closed()), this, SLOT(slot_gameClose()));
}

void API::connect_Game_graphic()
{
    connect(this->getGameGraphics(), SIGNAL(signal_game_closed()), this, SLOT(slot_gameClose()));
}

void API::connect_Container()
{
    connect(this->getGameContainer(), SIGNAL(signal_update_current()), this->getGameNetwork(), SLOT(slot_update()));

    connect(this->getGameContainer(), SIGNAL(signal_update_all()), this->getGameGraphics(), SLOT(slot_update()));

    connect(this->getGameContainer(), SIGNAL(signal_closed()), this, SLOT(slot_gameClose()));
}

void API::connect_MainWindow_cnnect()
{
    connect(this->getMainWindow(), SIGNAL(signal_button_connect(QString, QString)), this->getGameNetwork(), SLOT(slot_connect(QString, QString)));

    connect(this->getMainWindow(), SIGNAL(signal_closed()), this, SLOT(slot_gameClose()));
}

void API::connect_all()
{
    this->connect_Game_graphic();
    this->connect_Game_net();
    this->connect_Container();
    this->connect_MainWindow_cnnect();
}
