#include "network_main.h"
#include <QDebug>

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
    bool fl = false;
    if (!this->status)
    {
        this->soc = new QUdpSocket(this);
        this->status = this->soc->bind(this->portToRead);
        if (this->status)
        {
//            qDebug() << QString("______________________________________________________________________________");
//            qDebug() << QString(" SOCKET-->> Socket was been binded on port (read) ") + QString::number(this->getPortToRead());
//            qDebug() << QString("       -->> Socket was been binded on port (send) ") + QString::number(this->getPortToSend());
//            qDebug() << QString("______________________________________________________________________________");
            connect(this->soc, SIGNAL(readyRead()), this, SLOT(readDataGram()));
            fl = true;
        }
        else
        {
//            qDebug() << QString("______________________________________________________________________________");
//            qDebug() << " SOCKET-->> Socket was NOT been binded";
//            qDebug() << QString("______________________________________________________________________________");
            delete this->soc;
            fl = false;
        }
    }
    return fl;
}

void network_main::readDataGram()
{
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
}

void network_main::sendMessage(QByteArray &DATA, QHostAddress IP)
{
    if (this->getStatus())
    {
        //qDebug() << QString(" SOCKET-->> Send message on ") + IP.toString() + QString(":") + QString::number(this->portToSend);

        //send on IP:portToSend data
        this->soc->writeDatagram(DATA, IP, this->portToSend);
    }
}


