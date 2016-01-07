#ifndef FORM_H
#define FORM_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QUdpSocket>
#include "player.h"

class Form : public QGLWidget
{
    Q_OBJECT

public:
    Form(QString player_name, QWidget* parent = 0);
    //void getPlayers();//if they are online they do nothing, else they add new player to list

    void sendPosition(QDataStream&);//do it, if player move
    void sendAngle(QDataStream&);//do it, if player change his angle
    //void sendWeapon(QDataStream&);//dp it, if player change weapon
    void sendHealth(QDataStream&);//do it, if player change hp
    void sendArmor(QDataStream&);//do it, if player change armor
    //void sendFire(QDataStream&);//do it, if player shoot
    void sendBegin(QDataStream&, QString);//need for more better code
    void sendEnd(QByteArray&, QDataStream&);//need for more better code
    void send(int);//main type of 'send'

    int searchPlayer(QHostAddress, QString);
    void setServerAddress(const QHostAddress);

protected:
    //FOR OPENGL
    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void geese(float, float, float, float);//рисование квадратика
    //methods
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent *);

private:
    //server/socket
    QUdpSocket *soc;
    int p_port;
    int s_port;

    //opengl
    int m_width;
    int m_height;

    //db
    Player *pl;
    QList<Player*> players;
    QHostAddress s_address;


public slots:
    void readMessage();

};

#endif // FORM_H
