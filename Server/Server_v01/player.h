#ifndef PLAYER_H
#define PLAYER_H

#define toRADIAN(angle) (M_PI * angle / 180)
#define toDEGREE(x) (x * 180 / M_PI)

#include <QObject>
#include <QString>
#include <QHostAddress>

enum COMMAND {_online, _position, _armor, _health, _angle, _login};

class Player : public QObject
{
public:
    Player(QHostAddress ip, QString name, float x = rand() % 100, float y = rand() % 100, float angle = 0, int health = 100, int armor = 100, QObject *parent = 0);
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

    static QString _CMD(COMMAND cmd)
    {
        switch(cmd)
        {
        case _online: return "_online";
        case _position: return "_position";
        case _armor: return "_armor";
        case _health: return "_health";
        case _angle: return "_angle";
        case _login: return "_login";
        }
    }

    static COMMAND _CMD(QString cmd)
    {
        if (cmd == QString::fromStdString("_online")) return _online;
        if (cmd == QString::fromStdString("_position")) return _position;
        if (cmd == QString::fromStdString("_armor")) return _armor;
        if (cmd == QString::fromStdString("_health")) return _health;
        if (cmd == QString::fromStdString("_angle")) return _angle;
        if (cmd == QString::fromStdString("_login")) return _login;
    }

signals:
    void changed_position();
    void changed_health();
    void changed_armor();
    void changed_angle();
    void changed_fire();

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

#endif // PLAYER_H
