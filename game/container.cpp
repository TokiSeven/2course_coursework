#include "container.h"

Container::Container(QString pl_name, QHostAddress s_ip, quint16 s_port, quint16 p_port, QObject *parent) : QObject(parent)
{
    //qDebug() << QString("Container-->> ") + "Created.";
    this->server_ip = s_ip;
    this->server_port = s_port;
    this->player_port = p_port;

    pl.setIp(QHostAddress::LocalHost);
    pl.name = pl_name.toStdString();
    pl.setOnline(true);
}

Container::~Container()
{
    //qDebug() << QString("Container-->> ") + "~Container()";
    //emit signal_closed();
}

void Container::slot_game_close()
{
    //qDebug() << QString("Container-->> ") + "slot_game_close()";
    emit signal_closed();
}

void Container::updatePlayers(QList<Data> players)
{
    players.clear();
    players.append(players);
    emit signal_update_all();
}

void Container::deletePlayer(int num)
{
    if (num >= 0 && num < players.size())
    {
        players.removeAt(num);
        emit signal_update_all();
    }
}

void Container::updatePlayer(Data pl)
{
    int num = players.indexOf(pl);
    if (num != -1)
    {
        players[num] = pl;
        emit signal_update_current();
    }
    else
    {
        if (this->pl.getName() == pl.getName())
        {
            this->pl = pl;
            emit signal_update_all();
        }
        else
        {
            this->players.append(pl);
            emit signal_update_current();
        }
    }
}

void Container::setServerIp(QHostAddress ip)
{
    this->server_ip = ip;
}
