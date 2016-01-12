#ifndef PLAYER_H
#define PLAYER_H

#define toRADIAN(angle) (M_PI * angle / 180)
#define toDEGREE(x) (x * 180 / M_PI)

#include <QString>
#include <QHostAddress>

enum COMMAND {_online, _position, _armor, _health, _angle, _login};

class Player
{
public:
    Player(QHostAddress ip, QString name, float x = rand() % 100, float y = rand() % 100, float angle = 0, int health = 100, int armor = 100);
    ~Player();

    void setName(const QString);
    void setIp(const QHostAddress);
    void setX(const float);
    void setY(const float);
    void setAngle(const float);
    void setHealth(const int);
    void setArmor(const int);
    void setWidth(const float);
    void setHeight(const float);

    const QString getName()const{return this->name;}
    const QHostAddress getIp()const{return this->ip;}
    const float getX()const{return this->x;}
    const float getY()const{return this->y;}
    const float getAngle()const{return this->angle;}
    const int getHealth()const{return this->health;}
    const int getArmor()const{return this->armor;}
    const float getWidth()const{return this->width;}
    const float getHeight()const{return this->height;}

private:
    QHostAddress ip;//ip of player
    QString name;//player's name
    float x;//position (x) of player
    float y;//position (y) of player
    float angle;//rotation of player
    int health;//health of player
    int armor;//armor of player
    float width;
    float height;
};

#endif // PLAYER_H
