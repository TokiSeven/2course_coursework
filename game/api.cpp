#include "api.h"

API::API(QObject *parent) : QObject(parent)
{
    this->mw = new MainWindow_connect();
    this->cont = new Container(QString("NoName"), QHostAddress("127.0.0.1"), 1100, 2200, (QObject*)this);
    this->game_net = new Game_net(cont, (QObject*)this);
    this->game_graph = new Game_graphic(cont);

    isGame = false;

    this->connect_all();
}

API::~API()
{
    delete this->game_graph;
    delete this->game_net;
    delete this->cont;
    delete this->mw;
}

void API::startGame()
{
    //Create a thread for graphic part

    //    QThread *thread = new QThread;
    //    game_graph->moveToThread(thread);
    //    connect(thread, SIGNAL(started()), game_graph, SLOT(slot_game_start()));
    //    connect(game_graph, SIGNAL(signal_game_closed()), thread, SLOT(quit()));
    //    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //    thread->start();
    if (!isGame)
    {
        game_graph->slot_game_start();
        isGame = true;
    }
}

void API::slot_startGame()
{
    this->startGame();
}

void API::slot_gameClose()
{
    if (isGame)
    {
        this->getGameGraphics()->slot_close();
        this->getGameNetwork()->slot_game_close();
        this->getGameContainer()->slot_game_close();
        this->getMainWindow()->game_closed();
    }
}

void API::slot_refreshGame()
{
}

void API::connect_Game_net()
{
    Game_net *game = this->getGameNetwork();

    connect(game, SIGNAL(connected()), this->getMainWindow(), SLOT(answerTrue()));
    connect(game, SIGNAL(connected()), this, SLOT(slot_startGame()));

    connect(game, SIGNAL(disconnected()), this, SLOT(slot_gameClose()));
    connect(game, SIGNAL(disconnected()), this->getMainWindow(), SLOT(serverTimeout()));

    connect(game, SIGNAL(nick_incorrect()), this->getMainWindow(), SLOT(answerFalse()));

    connect(game, SIGNAL(signal_closed()), this, SLOT(slot_gameClose()));

    connect(game, SIGNAL(signal_keyPressed(QString,QString)), this->getGameGraphics(), SLOT(slot_keyPress(QString,QString)));
}

void API::connect_Game_graphic()
{
    Game_graphic *game = this->getGameGraphics();

    connect(game, SIGNAL(signal_game_closed()), this, SLOT(slot_gameClose()));

    connect(game, SIGNAL(signal_keyPressed(QString)), this->getGameNetwork(), SLOT(slot_keyPress(QString)));
}

void API::connect_Container()
{
    Container *cont = this->getGameContainer();

    connect(cont, SIGNAL(signal_update_current()), this->getGameNetwork(), SLOT(slot_update()));

    connect(cont, SIGNAL(signal_update_all()), this->getGameGraphics(), SLOT(slot_update()));

    connect(cont, SIGNAL(signal_closed()), this, SLOT(slot_gameClose()));
}

void API::connect_MainWindow_connect()
{
    MainWindow_connect *launcher = this->getMainWindow();

    connect(launcher, SIGNAL(signal_button_connect(QString, QString)), this->getGameNetwork(), SLOT(slot_connect(QString, QString)));

    connect(launcher, SIGNAL(signal_closed()), this, SLOT(slot_gameClose()));
}

void API::connect_Player_Current()
{
    Data *player = this->getGameContainer()->getPlayer_current_pointer();
}

void API::connect_all()
{
    this->connect_Game_graphic();
    this->connect_Game_net();
    this->connect_Container();
    this->connect_MainWindow_connect();
}
