#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <client.h>
#include <QUdpSocket>
#include "player.h"

struct s_login_pass
{
    QString login;
    QString pass;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void update();//update GUI
    bool checkAuth(const QString, const QString);//check authorization
    int searchPlayer(QHostAddress, QString);
    //need for resend to players
    void sendPosition(Player*);//do it, if player move
    void sendAngle(Player*);//do it, if player change his angle
    void sendHealth(Player*);//do it, if player change hp
    void sendArmor(Player*);//do it, if player change armor
    void sendBegin(QDataStream&, QString, Player*);//need for more better code
    void sendEnd(QByteArray&, QDataStream&, Player*);//need for more better code
    //remove players from launcher & game
    void removePlayerIp(QString);

private:
    Ui::MainWindow *ui;

    QTcpServer *tcpServer;//tcp server
    QUdpSocket *socServer;//udp socket server

    int server_status;

    QList<Client*> Clients;//base of tcp clients (connection)
    QList<s_login_pass> db_clients;//database with logins & passwords
    QList<Player*> players;

    quint16 tcp_s_port;//server port for tcp connection
    quint16 udp_s_port;//server port for udp connection
    quint16 udp_p_port;
    QString tcp_s_ip;//server ip for tcp connection
    QString udp_s_ip;//server ip for udp connection

private slots:
    void newUser();//connect new user from tcp
    void on_button_stop_server_clicked();//stop server
    void on_button_start_server_clicked();//start server
    void on_pushButton_clicked();//clear info
    void readPacketUdp();//read info from game player
    void readInfoFromClient();//some message from client's launcher
    void disconnectClient();//disc clients (tcp)
};

#endif // MAINWINDOW_H
