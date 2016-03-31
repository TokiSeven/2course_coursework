#ifndef CONTAINER_H
#define CONTAINER_H

#include <QObject>
#include <QString>
#include "../Server/player.h"

class Container : public QObject
{
    Q_OBJECT
public:
    explicit Container(QString pl_name, QHostAddress s_ip, quint16 s_port = 1100, quint16 p_port = 2201, QObject *parent = 0);
    ~Container();

    inline QList<Player*> getPlayer_all()const{return this->players;}
    inline Player* getPlayer_current()const{return this->pl;}
    inline QHostAddress getServerIp()const{return this->server_ip;}
    inline quint16 getServerPort()const{return this->server_port;}
    inline quint16 getPlayerPort()const{return this->player_port;}

signals:
    void signal_closed();

public slots:
    void slot_game_close();

private:
    QHostAddress server_ip;
    quint16 server_port;
    quint16 player_port;
    QList<Player*> players;
    Player *pl;
};

#endif // CONTAINER_H
