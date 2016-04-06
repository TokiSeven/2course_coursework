#include "server.h"
#include <QDebug>
//                          ===============
//                          <<__CONSTRUCTOR
//                          ===============
Server::Server(quint16 port_s, quint16 port_p, quint16 port_l, QObject *parent) : QObject(parent)
{
    this->udp_p_port = port_p;
    this->udp_s_port = port_s;
    this->udp_l_port = port_l;
    this->server_status = false;
    this->socServer = NULL;
    this->timer_to_ask.setInterval(3000);
    this->timer_to_ask.start();
    connect(&timer_to_ask, SIGNAL(timeout()), this, SLOT(checkWhoIsHere()));
}

//                          =================
//                          <<__START SERVER
//                          =================
bool Server::start()
{
    if (!server_status)
    {
        socServer = new QUdpSocket;
        socServer->bind(udp_s_port);
        connect(socServer, SIGNAL(readyRead()), this, SLOT(readPacketUdp()));
        server_status = true;
        emit started();
        return true;
    }
    else
        return false;
}

//                          ===============
//                          <<__STOP SERVER
//                          ===============
bool Server::stop()
{
    if (server_status)
    {
        delete socServer;
        emit stoped();
        this->server_status = false;
        return true;
    }
    else
        return false;
}

//                          ===============================
//                          <<__READ DATAGRAMS FROM PLAYERS
//                          ===============================
void Server::readPacketUdp()
{
    QByteArray datagram;
    datagram.resize(socServer->pendingDatagramSize());
    QHostAddress *address = new QHostAddress;
    socServer->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
        in >> size;
    else
        return;
    if (in.device()->size() - sizeof(qint64) < size)
        return;

    QString pl_name, cmd_qs;

    in >> pl_name;
    in >> cmd_qs;

    COMMAND cmd = Player::_CMD(cmd_qs);

    qDebug() << pl_name + QString::fromStdString(" || ") + cmd_qs;

    if (cmd == _login)
    {
        bool been = false;
        for (int i = 0; i < players.size(); i++)
            if (players[i].getName() == pl_name)
                been = true;
        if (been)
        {
            sendAuth(*address, false);
        }
        else
        {
            sendAuth(*address, true);

            Player plr(*address, pl_name);
            int num = players.size();

            players.append(plr);
            players[num].setIp(*address);

            send(players[num], sendPlayer);
            emit update();
        }
        return;
    }

    //search id of players, who sent message
    //if he have not in list, they add to this and set id as last
    int j = searchPlayer(*address, pl_name);

    if (j == -1)
    {
        players.append(*(new Player(*address, pl_name)));
        j = players.size() - 1;
    }

    //================================================================
    //                                big 'if' for command from player
    //================================================================
    if (cmd == _update)
    {
        Player pl;
        in >> pl;
        players[j](pl);
        send(players[j], sendPlayer);
    }
    else if (cmd == _online)
    {
        players[j].setOnline(true);
    }
    emit update();
}

//                          ====================================
//                          <<__SEARCHING PLAYERS BY NAME AND IP
//                          ====================================
int Server::searchPlayer(QHostAddress address, QString pl_name)
{
    int j = -1;
    for (int i = 0; i < players.size() && j == -1; i++)
        if (players[i].getIp() == address && players[i].getName() == pl_name)
            j = i;
    return j;
}


//                          ======================
//                          <<__CHECK AUTHORIZTING
//                          ======================
bool Server::checkAuth(const QString login)
{
    for (int i = 0; i < players.size(); i++)
        if (players[i].getName() == login)
            return false;
    return true;
}

//                          ================================
//                          <<__SENDING TO PLAYERS MAIN VIEW
//                          ================================
void Server::send(Player pl, void (Server::*fnc)(QDataStream&, Player))
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << pl.getName();

    (this->*fnc)(out, pl);

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    for (int i = 0; i < players.size(); i++)
        if (players[i].getName() != pl.getName())
        {
            socServer->writeDatagram(data, players[i].getIp(), this->udp_p_port);
            qDebug() << players[i].getIp().toString();
        }
}

//                          =====================
//                          <<__SENDING PLAYER
//                          =====================
void Server::sendPlayer(QDataStream &out, Player pl)
{
    out << Player::_CMD(_update);
    out << pl;
}

//                          ==========================
//                          <<__SENDING ASK TO PLAYERS
//                          ==========================
void Server::checkWhoIsHere()
{
    //delete all, who before this did not asked that he is online
    int size = players.size();
    for (int i = 0; i < players.size();)
    {
        if (!players[i].getOnline())
            players.removeAt(i);
        else
            i++;
    }

    //reset status of all players
    for (int i = 0; i < players.size(); i++)
        players[i].setOnline(false);

    if (size != players.size())
        sendPlayersToAll();

    emit update();
}

//                          ============================
//                          <<__SENDING TRUE AUTH FOR IP
//                          ============================
void Server::sendAuth(QHostAddress addr, bool flag)
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    QString answer;
    if (flag)
    {
        answer = "YES";
    }
    else
    {
        answer = "NO";
    }

    out << qint64(0);
    out << QString::fromStdString("SERVER");
    out << Player::_CMD(_login);
    out << answer;

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    socServer->writeDatagram(data, addr, this->udp_l_port);
}

void Server::sendPlayersToAll()
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << QString::fromStdString("SERVER");
    out << Player::_CMD(_players);
    out << this->players;


    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    for (int i = 0; i < players.size(); i++)
        socServer->writeDatagram(data, players[i].getIp(), this->udp_p_port);
}
