#include "client.h"

Client::Client()
{
    this->setX(0);
    this->setY(0);
    this->setName("");
    this->setBlockSize(0);
    this->setSocket(NULL);
    this->setAuth(false);
}

Client::Client(QTcpSocket *socket, QString name = "", int x = 0, int y = 0)
{
    this->setX(x);
    this->setY(y);
    this->setName(name);
    this->setSocket(socket);
    this->setBlockSize(0);
    this->setAuth(false);
}

void Client::setX(const int x)
{
    this->x = x;
}

void Client::setY(const int y)
{
    this->y = y;
}

void Client::setName(const QString name)
{
    if (name == "")
        this->Name = "Player";
    else
        this->Name = name;
}

void Client::setSocket(QTcpSocket *socket)
{
    if (socket)
        this->soc = socket;
}

void Client::setBlockSize(const quint16 size)
{
    this->blockSize = size;
}

void Client::setAuth(bool flag)
{
    this->Auth = flag;
}
