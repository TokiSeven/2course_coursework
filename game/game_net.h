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
    void sendPlayer(QDataStream&);//do it, if player move
    void sendOnline(QDataStream&);//do it on timer

signals:
    void signal_closed();
    void signal_update();

public slots:
    void slot_game_close();
    void slot_update();

private slots:
    void send_online();
    void readDatagramUdp();
    //void slot_time_out();

private:
    void checkData(QDataStream&);
    int searchPlayer(QHostAddress, QString);

    QTimer timer;
    QTimer timer_server_answer;//it will be, if server goes offline

    Container *cont;
    QUdpSocket *soc;
    quint16 p_port;
};

#endif // GAME_NET_H
