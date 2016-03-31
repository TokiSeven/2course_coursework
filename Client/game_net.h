#ifndef GAME_NET_H
#define GAME_NET_H

#include <QObject>
#include "container.h"
#include <QUdpSocket>
#include <QString>
#include <QDataStream>
#include <QTimer>

class Game_net : public QObject
{
    Q_OBJECT
public:
    explicit Game_net(Container *cont, QObject *parent = 0);
    ~Game_net();

    void send(void (Game_net::*fnc)(QDataStream &));
    void sendPosition(QDataStream&);//do it, if player move
    void sendAngle(QDataStream&);//do it, if player change his angle
    void sendHealth(QDataStream&);//do it, if player change hp
    void sendArmor(QDataStream&);//do it, if player change armor
    void sendOnline(QDataStream&);//do it on timer

signals:
    void signal_closed();

public slots:
    void slot_game_close();

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
};

#endif // GAME_NET_H
