#include "server.h"
#include <QDebug>

//=========================================
//                          <<__CONSTRUCTOR
//=========================================
Server::Server(QObject *parent, quint16 port_s, quint16 port_l)
    : network_main(port_l, port_s, parent)
{
    this->timer_to_ask.setInterval(5000);
    this->timer_to_ask.start(5000);
    connect(&timer_to_ask, SIGNAL(timeout()), this, SLOT(checkWhoIsHere()));
}

//==========================================
//                          <<__DESTSTRUCTOR
//==========================================
Server::~Server()
{
}


//=========================================================
//                          <<__READ DATAGRAMS FROM PLAYERS
//=========================================================
void Server::check_data(QDataStream &in, QHostAddress ip)
{
    QString pl_name, cmd_qs;

    in >> pl_name;
    in >> cmd_qs;

    COMMAND cmd = Player_old::_CMD(cmd_qs);

    qDebug() << QString("server >> NICK: ") + pl_name + QString("::") + cmd_qs;

    if (cmd == _login)
    {
        bool been = false;
        for (int i = 0; i < players.size(); i++)
            if (players[i].getName() == pl_name)
                been = true;
        if (been)
            sendAuth(ip, false);
        else
        {
            sendAuth(ip, true);

            Player_old plr(ip, pl_name);
            int num = players.size();

            players.append(plr);
            players[num].setIp(ip);

            sendPlayer(players[num]);
            emit signal_newPlayer(players[num].getName());
        }
        return;
    }

    //search id of players, who sent message
    //if he have not in list, they add to this and set id as last
    int j = searchPlayer(ip, pl_name);

    if (j == -1)
        return;
    else
        players[j].setOnline(true);

    //=================================================================
    //                            <<__big 'if' for commands from player
    //=================================================================
    if (cmd == _update)
    {
        Player_old pl;
        in >> pl;
        players[j](pl);
        players[j].setIp(ip);
        sendPlayer(players[j]);
    }
}

//==============================================================
//                          <<__SEARCHING PLAYERS BY NAME AND IP
//==============================================================
int Server::searchPlayer(QHostAddress address, QString pl_name)
{
    int j = -1;
    for (int i = 0; i < players.size() && j == -1; i++)
        if (players[i].getIp() == address && players[i].getName() == pl_name)
            j = i;
    return j;
}


//================================================
//                          <<__CHECK AUTHORIZTING
//================================================
bool Server::checkAuth(const QString login)
{
    for (int i = 0; i < players.size(); i++)
        if (players[i].getName() == login)
            return false;
    return true;
}

//============================================
//                          <<__SENDING PLAYER
//============================================
void Server::sendPlayer(Player_old pl)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << pl.getName();
    out << Player_old::_CMD(_update);
    out << pl;

    for (int i = 0; i < players.size(); i++)
        if (pl.getName() != players[i].getName())
            this->sendMessage(data, players[i].getIp());
}

//====================================================
//                          <<__SENDING ASK TO PLAYERS
//====================================================
void Server::checkWhoIsHere()
{
    if (this->getStatus())
    {
        qDebug() << "CYCLE FOR PLAYERS TO DELETE OR NOT THEM";
        //delete all, who before this did not ask that he is online
        int size = players.size();
        for (int i = 0; i < players.size();)
        {
            if (!players[i].getOnline())
            {
                QString temp = players[i].getName();
                players.removeAt(i);
                emit signal_deletePlayer(temp);
            }
            else
                i++;
        }

        //reset status of all players
        for (int i = 0; i < players.size(); i++)
            players[i].setOnline(false);

        if (size != players.size())
            sendPlayersToAll();
    }
}

//======================================================
//                          <<__SENDING TRUE AUTH FOR IP
//======================================================
void Server::sendAuth(QHostAddress addr, bool flag)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    QString str = (flag) ? QString::fromStdString("YES") : QString::fromStdString("NO");

    out << QString::fromStdString("SERVER");
    out << Player_old::_CMD(_login);
    out << str;

    this->sendMessage(data, addr);
}

//================================================================
//                          <<__SENDING ALL PLAYERS TO ALL CLIENTS
//================================================================
void Server::sendPlayersToAll()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << QString::fromStdString("SERVER");
    out << Player_old::_CMD(_players);
    out << this->players;

    for (int i = 0; i < players.size(); i++)
        this->sendMessage(data, players[i].getIp());
}
