#include "game_net.h"

Game_net::Game_net(Container *cont, QObject *parent) : QObject(parent)
{
    this->cont = cont;
    this->p_port = 2201;
    soc = new QUdpSocket;
    soc->bind(cont->getPlayerPort());

    timer.setInterval(1000);
    timer.start();

    connect(&timer, SIGNAL(timeout()), this, SLOT(send_online()));

    connect(this->cont, SIGNAL(signal_closed()), this, SLOT(slot_game_close()));
    connect(this, SIGNAL(signal_closed()), this->cont, SLOT(slot_game_close()));
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
    out << cont->getPlayer_current()->getName();

    (this->*fnc)(out);

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    soc->writeDatagram(data, cont->getServerIp(), cont->getServerPort());
}

//                          =====================
//                          <<__SENDING POSITION
//                          =====================
void Game_net::sendPosition(QDataStream &out)
{
    out << Player::_CMD(_position);
    out << cont->getPlayer_current()->getX();
    out << cont->getPlayer_current()->getY();
}

//                          =================
//                          <<__SENDING ANGLE
//                          =================
void Game_net::sendAngle(QDataStream &out)
{
    out << Player::_CMD(_angle);
    out << cont->getPlayer_current()->getAngle();
}

//                          ==================
//                          <<__SENDING HEALTH
//                          ==================
void Game_net::sendHealth(QDataStream &out)
{
    out << Player::_CMD(_health);
    out << cont->getPlayer_current()->getHealth();
}

//                          =================
//                          <<__SENDING ARMOR
//                          =================
void Game_net::sendArmor(QDataStream &out)
{
    out << Player::_CMD(_armor);
    out << cont->getPlayer_current()->getArmor();
}

//                          =================
//                          <<__SENDING ONLINE
//                          =================
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
}

void Game_net::slot_game_close()
{
    emit signal_closed();
//    if (this)
//        delete this;
}