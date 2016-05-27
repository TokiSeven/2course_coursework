#ifndef CONTAINER_H
#define CONTAINER_H

#include <QObject>
#include <QString>
#include <QHostAddress>
#include "data.h"

class Container
        : public QObject
{
    Q_OBJECT
public:
    explicit Container(QString pl_name, QHostAddress s_ip, quint16 s_port = 1100, quint16 p_port = 2200, QObject *parent = 0);
    ~Container();

    void updatePlayers(QList<Data> players);
    void deletePlayer(int num);
    void updatePlayer(Data pl);

    void setServerIp(QHostAddress);

    inline int getPlayersSize()const{return this->players.size();}
    inline QList<Data> getPlayer_all()const{return this->players;}
    inline QList<Data>* getPlayer_all_pointer(){return &this->players;}
    inline Data getPlayer_current()const{return this->pl;}
    inline Data* getPlayer_current_pointer(){return &this->pl;}
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
    QList<Data> players;
    Data pl;
};

#endif // CONTAINER_H
