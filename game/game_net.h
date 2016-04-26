#ifndef GAME_NET_H
#define GAME_NET_H

#include "container.h"
#include <QTimer>
#include "../server/network_main.h"

class Game_net : public network_main
{
    Q_OBJECT
public:
    explicit Game_net(Container *cont, QObject *parent = 0);
    ~Game_net();

    void connectToServer(const QString serv_ip, QString pl_name);//connect to server on ip "serv_ip"

signals:
    void signal_closed();
    void signal_update();
    void connected();
    void disconnected();
    void nick_incorrect();

public slots:
    void slot_game_close();
    void slot_update();
    void slot_connect(QString nick, QString server);

private slots:
    void send_online();
    void timeOut();

protected:
    void check_data(QDataStream &, QHostAddress);

private:
    void sendPlayer();//do it, if player move
    void sendOnline();//do it on timer

    int searchPlayer(QHostAddress, QString);

    QTimer timer, timer_answer;
    QTimer timer_server_answer;//it will be, if server goes offline

    Container *cont;
};

#endif // GAME_NET_H
