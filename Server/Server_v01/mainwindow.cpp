#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
//#include "../client/player.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer_to_ask.setInterval(1000);
    timer_to_ask.start();

    connect(&timer_to_ask, SIGNAL(timeout()), this, SLOT(sendAskWhoIsHere()));

    ui->setupUi(this);
    server_status = 0;
    tcpServer = NULL;
    socServer = NULL;

    tcp_s_port = 1234;
    udp_p_port = 1235;
    udp_s_port = 1236;
    tcp_s_ip = "192.168.199.3";//"25.107.188.21";
    udp_s_ip = "192.168.199.3";//"25.107.188.21";
    /*tcp_s_ip = "95.84.146.28";
    udp_s_ip = "95.84.146.28";*/

    //load db
    QString fileName = "db.txt";
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }
        db_clients.clear();
        QTextStream in(&file);
        s_login_pass lp;
        int i = 1;
        while(!in.atEnd())
        {
            QString currentLine = in.readLine(20);
            if (currentLine != "/n")
                if (i == 1)
                {
                    lp.login = currentLine;
                    i++;
                }
                else if (i == 2)
                {
                    lp.pass = currentLine;
                    i--;
                    db_clients.append(lp);
                }
        }
        file.close();
    }

    for (int i = 0; i < db_clients.size(); i++)
        qDebug() << db_clients[i].login << " && " << db_clients[i].pass;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newUser()
{
    if (server_status)
    {
        ui->list_debug->addItem("New connection!");
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

        qDebug() << clientSocket->peerAddress().toString();

        int idUserSocs = Clients.size();
        Clients.append(new Client);

        Clients[idUserSocs]->setSocket(clientSocket);

        connect(Clients[idUserSocs]->getSocket(), SIGNAL(readyRead()), this, SLOT(readInfoFromClient()));
        connect(Clients[idUserSocs]->getSocket(), SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(disconnectClient()));

        update();
    }
}

void MainWindow::on_button_stop_server_clicked()
{
    if (server_status)
    {
        for (int i = 0; i < Clients.count(); i++)
        {
            QTextStream os(Clients[i]->getSocket());
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            Clients[i]->getSocket()->close();
            Clients.removeAt(i);
        }
        tcpServer->close();
        ui->list_debug->addItem("Server stopped!");
        server_status = 0;
        ui->button_start_server->setEnabled(true);
        ui->button_stop_server->setEnabled(false);

        if (tcpServer)
            delete tcpServer;
        if (socServer)
            delete socServer;

        update();
    }
}

void MainWindow::on_button_start_server_clicked()
{
    if (!server_status)
    {
        tcpServer = new QTcpServer(this);
        if (!tcpServer->listen(QHostAddress::Any, tcp_s_port))
        {
            ui->list_debug->addItem(QObject::tr("Unable to start the server: %1").arg(tcpServer->errorString()));
        }
        else
        {
            connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newUser()));
            socServer = new QUdpSocket;
            socServer->bind(udp_s_port);
            connect(socServer, SIGNAL(readyRead()), this, SLOT(readPacketUdp()));
            server_status = 1;
            ui->list_debug->addItem("Server started!");
            ui->list_debug->addItem("Server tcp:" + tcp_s_ip + ":" + QString::number(tcp_s_port));
            ui->list_debug->addItem("Server udp:" + udp_s_ip + ":" + QString::number(udp_s_port));
            ui->button_start_server->setEnabled(false);
            ui->button_stop_server->setEnabled(true);
        }
        update();
    }
}

void MainWindow::readInfoFromClient()
{
    ui->list_debug->addItem("->New message:");
    QTcpSocket *sock = (QTcpSocket*)sender();

    int num = -1;
    for (int i = 0; i < Clients.size(); i++)
        if (Clients[i]->getSocket() == sock)
        {
            num = i;
            break;
        }

    if (num == -1)
        return;

    Client *client = Clients[num];

    QDataStream in(client->getSocket());

    if (!client->getBlockSize())
    {
        if (client->getSocket()->bytesAvailable() < (int)sizeof(quint16))
            return;
        quint16 bSize = 0;
        in >> bSize;
        client->setBlockSize(bSize);
    }
    if (client->getSocket()->bytesAvailable() <= client->getBlockSize())
        return;
    else
        client->setBlockSize(0);

    QString command;
    in >> command;

    ui->list_debug->addItem("--->COMMAND: " + command);

    if (command == "AUTH")
    {
        QString login, pass;
        in >> login;
        in >> pass;

        ui->list_debug->addItem("Login: " + login + " && Password: " + pass);

        if (checkAuth(login, pass))
        {
            QByteArray block;
            QDataStream sendStream(&block, QIODevice::WriteOnly);

            sendStream << quint16(0) << QString::fromUtf8("ANSWER") << QString::fromUtf8("YES");
            sendStream.device()->seek(0);
            sendStream << (quint16)(block.size() - sizeof(quint16));

            client->getSocket()->write(block);

            client->setName(login);

            client->setAuth(true);
        }
        else
        {
            QByteArray block;
            QDataStream sendStream(&block, QIODevice::WriteOnly);

            sendStream << quint16(0) << QString::fromUtf8("ANSWER") << QString::fromUtf8("NO");
            sendStream.device()->seek(0);
            sendStream << (quint16)(block.size() - sizeof(quint16));

            client->getSocket()->write(block);
        }
    }

    update();
}

void MainWindow::disconnectClient()
{
    Client *client = (Client*)sender();
    if (client->getSocket()->state() != QAbstractSocket::ConnectedState)
    {
        Clients.removeAll(client);
        update();
    }
}

void MainWindow::update()
{
    for(int i = 0; i < Clients.size(); i++)
    {
        if (Clients[i]->getSocket()->state() != QAbstractSocket::ConnectedState)
        {
            Clients[i]->getSocket()->close();
            Clients.removeAt(i);
        }
    }
    ui->data_numbers->setText(QString::number(Clients.size()));
    ui->list_player->clear();
    for (int i = 0; i < Clients.size(); i++)
        if (Clients[i]->getName() != "")
            ui->list_player->addItem(Clients[i]->getName());
}

void MainWindow::on_pushButton_clicked()
{
    ui->list_debug->clear();
}

bool MainWindow::checkAuth(const QString login, const QString pass)
{
    for (int i = 0; i < Clients.size(); i++)
        if (login == Clients[i]->getName())
            return false;
    for (int i = 0; i < db_clients.size(); i++)
        if (login == db_clients[i].login && pass == db_clients[i].pass)
            return true;
    return false;
}

void MainWindow::removePlayerIp(QString ip)
{
    int numTCP = -1, numUDP = -1;
    for (int i = 0; i < Clients.size() && numTCP == -1; i++)
        if (Clients[i]->getSocket()->localAddress() == QHostAddress(ip))
            numTCP = i;
    for (int i = 0; i < players.size() && numUDP == -1; i++)
        if (players[i]->getIp() == QHostAddress(ip))
            numUDP = i;
    if (numTCP != -1)
        Clients.removeAt(numTCP);
    if (numUDP != -1)
        players.removeAt(numUDP);
}

void MainWindow::readPacketUdp()
{
    QByteArray datagram;
    datagram.resize(socServer->pendingDatagramSize());
    QHostAddress *address = new QHostAddress;
    socServer->readDatagram(datagram.data(), datagram.size(), address);

    QDataStream in(&datagram, QIODevice::ReadOnly);

    qint64 size = -1;
    if(in.device()->size() > sizeof(qint64))
        in >> size;
    else
        return;
    if (in.device()->size() - sizeof(qint64) < size)
        return;

    QString pl_name;
    QString cmd;

    in >> pl_name;
    in >> cmd;

    //search id of players, who sent message
    //if he have not in list, they add to this and set id as last
    int j = searchPlayer(*address, pl_name);

    if (j == -1)
    {
        Player *new_pl = new Player(*address, pl_name);
        players.append(new_pl);
        j = players.size() - 1;
    }

    qDebug() << "j:" << j << " | address:" << address->toString() << " | pl_name:" << pl_name << " | cmd:" << cmd;

    //big 'if' for command from player
    if (cmd == "NEW_POSITION")
    {
        float x, y;
        in >> x;
        in >> y;
        players[j]->setX(x);
        players[j]->setY(y);
        sendPosition(players[j]);
    }
    else if (cmd == "NEW_ANGLE")
    {
        float angle;
        in >> angle;
        players[j]->setAngle(angle);
        sendAngle(players[j]);
    }
    else if (cmd == "NEW_HEALTH")
    {
        int health;
        in >> health;
        players[j]->setHealth(health);
        sendHealth(players[j]);
    }
    else if (cmd == "NEW_ARMOR")
    {
        int armor;
        in >> armor;
        players[j]->setArmor(armor);
        sendArmor(players[j]);
    }
    else if (cmd == "I_AM_HERE")
    {
        players[j]->setOnline(true);
    }
}

int MainWindow::searchPlayer(QHostAddress address, QString pl_name)
{
    int j = -1;
    for (int i = 0; i < players.size() && j == -1; i++)
        if (players[i]->getIp() == address && players[i]->getName() == pl_name)
            j = i;
    return j;
}

//-------------------------------------------------------
//----------SEND TO ALL PLAYERS FROM US-----------(BEGIN)
//-------------------------------------------------------
void MainWindow::sendBegin(QDataStream &out, QString command, Player *pl)
{
    out << qint64(0);
    out << pl->getName();
    out << command;
    qDebug() << "SEND TO name:" << pl->getName() << " | CMD:" << command;
}
void MainWindow::sendEnd(QByteArray &data, QDataStream &out, Player *pl)
{
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    for (int i = 0; i < players.size(); i++)
        if (players[i]->getName() != pl->getName())
            socServer->writeDatagram(data, players[i]->getIp(), this->udp_p_port);
    qDebug() << "END SENDING TO ip:" << pl->getIp().toString() << " | PORT:" << this->udp_p_port;
}
void MainWindow::sendPosition(Player *pl)
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    sendBegin(out, "NEW_POSITION", pl);

    //write here your data
    out << pl->getX();
    out << pl->getY();

    //---!!!it is default settings!!!---
    sendEnd(data, out, pl);
}
void MainWindow::sendAngle(Player *pl)
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    sendBegin(out, "NEW_ANGLE", pl);

    //write here your data
    out << pl->getAngle();

    //---!!!it is default settings!!!---
    sendEnd(data, out, pl);
}
void MainWindow::sendHealth(Player *pl)
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    sendBegin(out, "NEW_HEALTH", pl);

    //write here your data
    out << pl->getHealth();

    //---!!!it is default settings!!!---
    sendEnd(data, out, pl);
}
void MainWindow::sendArmor(Player *pl)
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    sendBegin(out, "NEW_ARMOR", pl);

    //write here your data
    out << pl->getArmor();

    //---!!!it is default settings!!!---
    sendEnd(data, out, pl);
}
void MainWindow::sendAskWhoIsHere()
{
    //delete all, who before this did not asked that he is online
    for (int i = 0; i < players.size();)
    {
        if (!players[i]->getOnline())
            removePlayerIp(players[i]->getIp().toString());
        else
            i++;
    }

    //reset status of all players
    for (int i = 0; i < players.size(); i++)
        players[i]->setOnline(false);

    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << QString::fromStdString("SERVER");
    out << QString::fromStdString("WHO_IS_HERE");

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    for (int i = 0; i < players.size(); i++)
        socServer->writeDatagram(data, players[i]->getIp(), this->udp_p_port);
}
void MainWindow::sendPlayerWhoIsHere()
{
    //---!!!it is default settings!!!---
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint64(0);
    out << QString::fromStdString("SERVER");
    out << QString::fromStdString("NICKS_WHO_HERE");

    for (int i = 0; i < players.size(); i++)
        out << players[i]->getName();

    //---!!!it is default settings!!!---
    out.device()->seek(qint64(0));
    out << qint64(data.size() - sizeof(qint64));
    for (int i = 0; i < players.size(); i++)
        socServer->writeDatagram(data, players[i]->getIp(), this->udp_p_port);
}
//-----------------------------------------------------
//----------SEND TO ALL PLAYERS FROM US-----------(END)
//-----------------------------------------------------
