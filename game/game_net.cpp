#include "game_net.h"

Game_net::Game_net(Container *cont, QObject *parent) : QObject(parent)
{
    this->cont = cont;
    this->p_port = 2201;
    soc = new QUdpSocket;
    soc->bind(cont->getPlayerPort());

    this->serv = NULL;

    timer.setInterval(1000);
    timer.start();

    connect(soc, SIGNAL(readyRead()), this, SLOT(readDatagramUdp()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(send_online()));

    connect(cont, SIGNAL(signal_update_all()), this, SLOT(slot_update()));
}

Game_net::~Game_net()
{
    emit signal_closed();
    //    if (this)
    //        delete this;
}

//                          ================================
//                          <<__SENDING TO PLAYERS MAIN VIEW
//                          ================================
void Game_net::send(void (Game_net::*fnc)(QDataStream&))
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << cont->getPlayer_current().getName();

    (this->*fnc)(out);

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    soc->writeDatagram(data, cont->getServerIp(), cont->getServerPort());
}

//                          =====================
//                          <<__SENDING PLAYER
//                          =====================
void Game_net::sendPlayer(QDataStream &out)
{
    out << Player::_CMD(_update);
    out << cont->getPlayer_current();
}

void Game_net::sendOnline(QDataStream &out)
{
    out << Player::_CMD(_online);
}

//                          =================
//                          <<__SENDING ONLINE_SLOT
//                          =================
void Game_net::send_online()
{
    send(sendOnline);
}

//                          ====================
//                          <<__READING DATAGRAM
//                          ====================
void Game_net::readDatagramUdp()
{
    qDebug() <<"sad";
    QByteArray datagram;
    datagram.resize(soc->pendingDatagramSize());
    soc->readDatagram(datagram.data(), datagram.size());

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
        in >> size;
    else
        return;
    if (in.device()->size() - sizeof(qint64) < size)
        return;

    checkData(in);
}

//                          ==================
//                          <<__CHECK DATAGRAM
//                          ==================
void Game_net::checkData(QDataStream &in)
{
    QString pl_name, cmd_qs;
    in >> pl_name;
    in >> cmd_qs;
    COMMAND cmd = Player::_CMD(cmd_qs);

    qDebug() << Player::_CMD(cmd);

    if (cmd == _update)
    {
        Player pl;
        in >> pl;
        cont->updatePlayer(pl);
    }
    else if (cmd == _players)
    {
        QList<Player> players;
        in >> players;
        cont->updatePlayers(players);
    }
}

void Game_net::slot_game_close()
{
    emit signal_closed();
    //    if (this)
    //        delete this;
}

void Game_net::slot_update()
{
    send(sendPlayer);
}


void Game_net::server_start()
{
    if (serv != NULL)
    {
        if (serv->getServerStatus())
            serv->stop();
        delete serv;
        serv = NULL;
    }
    serv = new Server;
    serv->start();
}
