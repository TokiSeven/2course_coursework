#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QDataStream>
#include "player.h"

struct s_login_pass
{
    QString login;
    QString pass;
};

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0, quint16 port_s = 1100, quint16 port_p = 2201, quint16 port_l = 2200);
    ~Server();

    //main func of the server
    bool start();//start the server
    bool stop();//stop the server

    //inline selectors
    inline bool getServerStatus()const{return this->server_status;}//return status of the server
    inline quint16 getServerPort()const{return this->udp_s_port;}//return port of the server
    inline quint16 getPlayerPort()const{return this->udp_p_port;}//return port of the players
    inline const QList<Player> getPlayers()const{return this->players;}//return all players

signals:
    void update();//when somthing is been
    void started();//when server is starting
    void stoped();//when server is stopping
    void error();//when some errors in starting or stopping of server

public slots:
    void readPacketUdp();//read info from player
    void checkWhoIsHere();//send on timer to all players and check their status

private:
    //need for resend to players
    void send(Player, void (Server::*fnc)(QDataStream &, Player));//you should to call this with funct to sending parametrs
    void sendPlayer(QDataStream&, Player);//do it, if player doing something
    void sendPlayerWhoIsHere();//check all who offline
    void sendAuth(QHostAddress, bool);//send to ip that he auth
    void sendPlayersToAll();//send all players to all

    bool checkAuth(const QString);//check authorization
    int searchPlayer(QHostAddress, QString);//search player by ip and name and return his number in list

    QUdpSocket *socServer;//udp socket server
    bool server_status;//online or offline
    QList<Player> players;//all players

    quint16 udp_s_port;//server port for udp connection
    quint16 udp_p_port;//port of players (send on this port)
    quint16 udp_l_port;//port of launcher (player don't connected but trying now)

    QTimer timer_to_ask;//timer for sending to players message "who are here?"
};

#endif // SERVER_H
