#include "Launcher_connect.h"

Launcher_connect::Launcher_connect(quint16 serv_port, quint16 ln_port, QObject *parent) : QObject(parent)
{
    this->server_port = serv_port;
    this->launcher_port = ln_port;

    socket = new QUdpSocket;
    socket->bind(ln_port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readUdpDiagrams()));
}

Launcher_connect::~Launcher_connect()
{
    emit signal_closed();
//    if (this)
//        delete this;
}

void Launcher_connect::connectToServer(const QString serv_ip, QString pl_name)
{
    this->player_name = pl_name;
    this->server_ip = QHostAddress(serv_ip);
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << pl_name;
    out << Player::_CMD(_login);

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    socket->writeDatagram(data, QHostAddress(serv_ip), this->server_port);

    timer.setInterval(2000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer.start();
}

void Launcher_connect::startGame()
{
    cont = new Container(this->player_name, this->server_ip);
    game_net = new Game_net(cont);
    game_graph = new Game_graphic(cont);

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

void Launcher_connect::timeOut()
{
    emit disconnected();
}

void Launcher_connect::readUdpDiagrams()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress;
    socket->readDatagram(datagram.data(), datagram.size(), address);

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

    if (cmd == _login && pl_name == QString::fromStdString("SERVER"))
    {
        timer.stop();
        QString ans;
        in >> ans;
        if (ans == QString::fromStdString("YES"))
        {
            this->server_ip = *address;
            emit connected();
        }
        else if (ans == QString::fromStdString("NO"))
        {
            emit nick_incorrect();
        }
    }
}


void Launcher_connect::slot_game_close()
{
    emit signal_closed();
//    if (this)
//        delete this;
}
