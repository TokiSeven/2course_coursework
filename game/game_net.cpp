#include "game_net.h"

Game_net::Game_net(Container *cont, QObject *parent)
    : network_main(cont->getServerPort(), cont->getPlayerPort(), parent)
{
    this->cont = cont;

    this->socketListen();

    timer.setInterval(1000);
    timer.start();

    timer_server_answer.setInterval(3000);
    timer_answer.setInterval(2000);
    timer_server_answer.start();

    connect(&timer, SIGNAL(timeout()), this, SLOT(send_online()));
    connect(&timer_server_answer, SIGNAL(timeout()), this, SLOT(slot_game_close()));
    connect(&timer_answer, SIGNAL(timeout()), this, SLOT(timeOut()));
    //connect(cont, SIGNAL(signal_update_all()), this, SLOT(slot_update()));
}

Game_net::~Game_net()
{
    //this->cont->slot_game_close();
    //emit signal_closed();
    //    if (this)
    //        delete this;
}

//                          =====================
//                          <<__SENDING PLAYER
//                          =====================
void Game_net::sendPlayer()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << Player::_CMD(_update);
    out << cont->getPlayer_current();

    this->sendMessage(data, cont->getServerIp());
}

void Game_net::sendOnline()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << Player::_CMD(_online);

    this->sendMessage(data, cont->getServerIp());
}

//                          =================
//                          <<__SENDING ONLINE_SLOT
//                          =================
void Game_net::send_online()
{
    sendOnline();
}

//                          ==================
//                          <<__CHECK DATAGRAM
//                          ==================
void Game_net::check_data(QDataStream &in, QHostAddress IP)
{
    QString pl_name, cmd_qs;
    in >> pl_name;
    in >> cmd_qs;
    COMMAND cmd = Player::_CMD(cmd_qs);

    qDebug() << pl_name + "::" + Player::_CMD(cmd);

    if (cmd == _update)
    {
        Player pl;
        in >> pl;
        cont->updatePlayer(pl);
    }
    else if (cmd == _players)
    {
        timer_server_answer.start();
        QList<Player> players;
        in >> players;
        cont->updatePlayers(players);
    }
    else if (cmd == _login && pl_name == QString::fromStdString("SERVER"))
    {
        timer.stop();
        QString ans;
        in >> ans;
        if (ans == QString::fromStdString("YES"))
        {
            this->cont->setServerIp(IP);
            emit connected();
        }
        else if (ans == QString::fromStdString("NO"))
        {
            emit nick_incorrect();
        }
    }
}

void Game_net::slot_game_close()
{
}

void Game_net::slot_update()
{
    sendPlayer();
}

void Game_net::connectToServer(const QString serv_ip, QString pl_name)
{
    Player pl(this->cont->getPlayer_current());
    pl.setName(pl_name);
    this->cont->updatePlayer(pl);

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << pl_name;
    out << Player::_CMD(_login);

    this->sendMessage(data, QHostAddress(serv_ip));

    timer_answer.start();
}

void Game_net::timeOut()
{
    emit disconnected();
}
