#ifndef SERVER_H
#define SERVER_H

#include <QTimer>
#include "../game/player.h"
#include "network_main.h"

class Server : public network_main
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0, quint16 port_s = 1100, quint16 port_l = 2200);
    ~Server();

    //inline selectors
    inline const QList<Player> getPlayers()const{return this->players;}//return all players

private slots:
    void checkWhoIsHere();//send on timer to all players and check their status

protected:
    void check_data(QDataStream&, QHostAddress);

private:
    //need for resend to players
    void sendPlayer(Player);//do it, if player doing something
    void sendPlayerWhoIsHere();//check all who offline
    void sendAuth(QHostAddress, bool);//send to ip that he auth
    void sendPlayersToAll();//send all players to all

    bool checkAuth(const QString);//check authorization
    int searchPlayer(QHostAddress, QString);//search player by ip and name and return his number in list

    QList<Player> players;//all players

    QTimer timer_to_ask;//timer for sending to players message "who are here?"
};

#endif // SERVER_H
