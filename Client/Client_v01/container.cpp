#include "container.h"

Container::Container(QString pl_name, QHostAddress s_ip, quint16 s_port, quint16 p_port, QObject *parent) : QObject(parent)
{
    this->server_ip = s_ip;
    this->server_port = s_port;
    this->player_port = p_port;
    pl = new Player(QHostAddress::LocalHost, pl_name);
    pl->setOnline(true);
}

Container::~Container()
{
    emit signal_closed();
//    if (this)
//        delete this;
}

void Container::slot_game_close()
{
    emit signal_closed();
//    if (this)
//        delete this;
}
