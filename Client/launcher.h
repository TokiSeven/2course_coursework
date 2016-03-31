#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "container.h"
#include "game_net.h"
#include "game_graphic.h"

class Launcher : public QObject
{
    Q_OBJECT
public:
    explicit Launcher(quint16 serv_port = 1100, quint16 ln_port = 2200, QObject *parent = 0);
    ~Launcher();

    void connectToServer(const QString serv_ip, QString pl_name);//connect to server on ip "serv_ip"
    void startGame();//start game, if setPlName & connect to server was been

    inline Game_net* getGameNetwork()const{return this->game_net;}
    inline Game_graphic* getGameGraphics()const{return this->game_graph;}
    inline Container* getGameContainer()const{return this->cont;}

signals:
    void connected();
    void disconnected();
    void nick_incorrect();
    void signal_closed();

public slots:
    void slot_game_close();
    void readUdpDiagrams();
    void timeOut();

private:
    QString player_name;
    QHostAddress server_ip;
    quint16 server_port;
    quint16 launcher_port;
    QTimer timer;

    QUdpSocket *socket;

    //for game
    Game_net *game_net;
    Game_graphic *game_graph;
    Container *cont;
};

#endif // LAUNCHER_H
