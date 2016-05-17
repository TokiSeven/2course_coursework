#ifndef CONTAINER_H
#define CONTAINER_H

#include <QObject>
#include <QString>
#include "player_old.h"

class Container : public QObject
{
    Q_OBJECT
public:
    explicit Container(QString pl_name, QHostAddress s_ip, quint16 s_port = 1100, quint16 p_port = 2200, QObject *parent = 0);
    ~Container();

    void updatePlayers(QList<Player_old> players);
    void addPlayer(Player_old player);
    void deletePlayer(int num);
    void updatePlayer(Player_old pl);

    void setServerIp(QHostAddress);

    inline QList<Player_old> getPlayer_all()const{return this->players;}
    inline QList<Player_old>* getPlayer_all_pointer(){return &this->players;}
    inline Player_old getPlayer_current()const{return this->pl;}
    inline Player_old* getPlayer_current_pointer(){return &this->pl;}
    inline QHostAddress getServerIp()const{return this->server_ip;}
    inline quint16 getServerPort()const{return this->server_port;}
    inline quint16 getPlayerPort()const{return this->player_port;}

signals:
    void signal_closed();
    void signal_update_current();
    void signal_update_all();

public slots:
    void slot_game_close();

private:
    QHostAddress server_ip;
    quint16 server_port;
    quint16 player_port;
    QList<Player_old> players;
    Player_old pl;
};

#endif // CONTAINER_H
