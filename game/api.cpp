#include "api.h"

API::API(QObject *parent) : QObject(parent)
{
    cont = new Container(QString("NoName"), QHostAddress("127.0.0.1"));
    game_net = new Game_net(cont);
    game_graph = new Game_graphic(cont);
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

    connect(cont, SIGNAL(signal_closed()), this, SLOT(slot_game_close()));
    connect(this, SIGNAL(signal_closed()), cont, SLOT(slot_game_close()));
}
