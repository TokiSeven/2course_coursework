#ifndef NETWORK_MAIN_H
#define NETWORK_MAIN_H

#include <QObject>
#include <QUdpSocket>
#include <QDataStream>
#include <QHostAddress>
#include <QMutex>

class network_main : public QObject
{
    Q_OBJECT
public:
    explicit network_main(quint16 port_send, quint16 port_read, QObject *parent = 0);
    ~network_main();

    //methods
    bool socketListen();

    //inline selectors
    inline bool getStatus()const{return this->status;}//return status of the server
    inline quint16 getPortToSend()const{return this->portToSend;}//return port of the server
    inline quint16 getPortToRead()const{return this->portToRead;}//return port of the players
    inline QUdpSocket* getSocket()const{return this->soc;}//return socket

private slots:
    void readDataGram();//read info

protected:
    virtual void check_data(QDataStream&, QHostAddress){}//check data from this QDataStream and this ip-address
    void sendMessage(QByteArray &DATA, QHostAddress IP);//send message from DATA to IP

    QMutex locker;
    QUdpSocket *soc;
    bool status;

    quint16 portToSend;//port for sending datagrams
    quint16 portToRead;//port for reading datagrams
};

#endif // NETWORK_MAIN_H
