#include "network_main.h"

network_main::network_main(quint16 port_send, quint16 port_read, QObject *parent)
    : QObject(parent)
{
    this->portToRead = port_read;
    this->portToSend = port_send;
    this->status = false;
}

network_main::~network_main()
{
    if (this->status)
        delete this->soc;
}

bool network_main::socketListen()
{
    locker.lock();
    bool fl = false;
    if (!this->status)
    {
        this->soc = new QUdpSocket(this);
        this->status = this->soc->bind(this->portToRead);
        if (this->status)
        {
            connect(this->soc, SIGNAL(readyRead()), this, SLOT(readDataGram()));
            fl = true;
        }
        else
        {
            delete this->soc;
            fl = false;
        }
    }
    locker.unlock();
    return fl;
}

void network_main::readDataGram()
{
    locker.lock();
    //datagram in wich will be message
    QByteArray datagram;

    //set size to this dg from message
    datagram.resize(this->soc->pendingDatagramSize());

    //initialization (this address - sender's ip)
    QHostAddress *address = new QHostAddress;

    //read datagram
    this->soc->readDatagram(datagram.data(), datagram.size(), address);

    //convert datagram to QDataStream (it will works easy)
    QDataStream in(&datagram, QIODevice::ReadOnly);

    //now we check our datagram
    this->check_data(in, *address);
    locker.unlock();
}

void network_main::sendMessage(QByteArray &DATA, QHostAddress IP)
{
    //locker.lock();
    if (this->getStatus())
    {
        //send on IP:portToSend data
        this->soc->writeDatagram(DATA, IP, this->portToSend);
    }
    //locker.unlock();
}


