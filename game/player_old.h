#ifndef PLAYER_OLD_H
#define PLAYER_OLD_H

#define toRADIAN(angle) (M_PI * angle / 180)
#define toDEGREE(x) (x * 180 / M_PI)

#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QDataStream>

enum COMMAND {_online, _update, _login, _connected, _disconnected, _error, _players};

class Player_old : public QObject
{
    Q_OBJECT
public:
    Player_old();
    Player_old(QHostAddress ip, QString name, float x = rand() % 100, float y = rand() % 100, float angle = 0, int health = 100, int armor = 100, QObject *parent = 0);
    Player_old(const Player_old&);
    ~Player_old();

    void setName(const QString);
    void setIp(const QHostAddress);
    void setX(const float);
    void setY(const float);
    void setAngle(const float);
    void setHealth(const int);
    void setArmor(const int);
    void setWidth(const float);
    void setHeight(const float);
    void setOnline(const bool);

    inline const QString getName()const{return this->name;}
    inline const QHostAddress getIp()const{return this->ip;}
    inline float getX()const{return this->x;}
    inline float getY()const{return this->y;}
    inline float getAngle()const{return this->angle;}
    inline int getHealth()const{return this->health;}
    inline int getArmor()const{return this->armor;}
    inline float getWidth()const{return this->width;}
    inline float getHeight()const{return this->height;}
    inline bool getOnline()const{return this->online;}

    Player_old operator =(const Player_old &pl);
    void operator ()(QString name, float x, float y, float angle, int health, int armor);
    void operator ()(const Player_old pl);

    bool operator ==(const Player_old player);

    friend QDataStream &operator <<(QDataStream &out, const Player_old pl)
    {
        out << pl.getName();
        out << pl.getX();
        out << pl.getY();
        out << pl.getAngle();
        out << pl.getHealth();
        out << pl.getArmor();

        return out;
    }

    friend QDataStream &operator >>(QDataStream &in, Player_old &pl)
    {
        QString name;
        float x;
        float y;
        float angle;
        int health;
        int armor;

        in >> name;
        in >> x;
        in >> y;
        in >> angle;
        in >> health;
        in >> armor;

        pl(name, x, y, angle, health, armor);

        return in;
    }

    static QString _CMD(COMMAND cmd)
    {
        QString ret;

        if (cmd == _online)
            ret = "_online";
        else if (cmd == _update)
            ret = "_update";
        else if (cmd == _login)
            ret = "_login";
        else if (cmd == _players)
            ret = "_players";
        else
            ret = "_error";

        return ret;
    }

    static COMMAND _CMD(QString cmd)
    {
        COMMAND ret;

        if (cmd == QString::fromStdString("_online"))
            ret = _online;
        else if (cmd == QString::fromStdString("_update"))
            ret = _update;
        else if (cmd == QString::fromStdString("_login"))
            ret = _login;
        else if (cmd == QString::fromStdString("_players"))
            ret = _players;
        else
            ret = _error;

        return ret;
    }

signals:
    void changed_update(Player_old*);

private:
    bool online;
    QHostAddress ip;//ip of the player
    QString name;//player's name
    float x;//position (x) of player
    float y;//position (y) of player
    float angle;//rotation of player
    int health;//health of player
    int armor;//armor of player
    float width;
    float height;
};
#endif // PLAYER_OLD_H
