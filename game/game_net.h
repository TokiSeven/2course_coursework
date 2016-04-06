#ifndef GAME_NET_H
#define GAME_NET_H

#include <QObject>
#include "container.h"
#include <QUdpSocket>
#include <QString>
#include <QDataStream>
#include <QTimer>
#include "server.h"

class Game_net : public QObject
{
    Q_OBJECT
public:
    explicit Game_net(Container *cont, QObject *parent = 0);
    ~Game_net();

    void send(void (Game_net::*fnc)(QDataStream &));
    void sendPlayer(QDataStream&);//do it, if player move
    void sendOnline(QDataStream&);//do it on timer

    //if player is server
    void server_start();

signals:
    void signal_closed();
    void signal_update();

public slots:
    void slot_game_close();
    void slot_update();

private slots:
    void send_online();
    void readDatagramUdp();

private:
    void checkData(QDataStream&);
    int searchPlayer(QHostAddress, QString);

    QTimer timer;

    Container *cont;
    QUdpSocket *soc;
    quint16 p_port;

    Server *serv;
};

#endif // GAME_NET_H
