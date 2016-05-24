#ifndef DATA_H
#define DATA_H

#include <string>
#include <QString>
#include <QHostAddress>
#include <QDataStream>

enum COMMAND {_online, _update, _login, _connected, _disconnected, _error, _players};

class Data
{
public:
    float x,y; // координаты
    float dx,dy,w,h; // скорость, ширина, высота
    bool life, dir; // существование объекта, направление
    float timer; // таймер
    std::string name; // имя объекта
    int Health; // здоровье
    bool online;
    QHostAddress ip;

    inline const QString getName()const{return QString::fromStdString(this->name);}
    inline const QHostAddress getIp()const{return this->ip;}

    Data toData()
    {
        Data r;
        r = (*((Data*)this));
        return r;
    }

    Data()
    {
        this->x = 0;
        this->y = 0;
        this->dir = 0;
        this->name = "NoName";
        this->dx = 0.0;
        this->dy = 0.0;
        this->w = 0.0;
        this->h = 0.0;
        this->Health = 0;
        this->life=true;
        this->timer=0;
        this->online = true;
    }

    Data(int X, int Y,std::string NAME, float DX, float DY, int HEALTH,bool DIR, float W, float H)
    {
        this->x = X;
        this->y = Y;
        this->dir = DIR;
        this->name = NAME;
        this->dx = DX;
        this->dy = DY;
        this->w = W;
        this->h = H;
        this->Health = HEALTH;
        this->life=true;
        this->timer=0;
        this->online = true;
    }

    Data(const Data &d)
    {
        this->dir = d.dir;
        this->dx = d.dx;
        this->dy = d.dy;
        this->h = d.h;
        this->w = d.w;
        this->Health = d.Health;
        this->life = d.life;
        this->name = d.name;
        this->online = d.online;
        this->x = d.x;
        this->y = d.y;
        this->timer = d.timer;
    }

    void setOnline(bool fl)
    {
        this->online = fl;
    }

    void setIp(const QHostAddress ip)
    {
        if (!ip.isNull())
        {
            this->ip = ip;
        }
    }

    bool operator ==(const Data &d)
    {
        return (this->getName() == d.getName() && this->getIp() == d.getIp()) ? true : false;
    }

    Data operator =(const Data &d)
    {
        this->dir = d.dir;
        this->dx = d.dx;
        this->dy = d.dy;
        this->h = d.h;
        this->w = d.w;
        this->Health = d.Health;
        this->life = d.life;
        this->name = d.name;
        this->online = d.online;
        this->x = d.x;
        this->y = d.y;
        this->timer = d.timer;
    }

    friend QDataStream &operator <<(QDataStream &out, const Data pl)
    {
        out << pl.getName();
        out << pl.x;
        out << pl.y;
        out << pl.dx;
        out << pl.dy;
        out << pl.h;
        out << pl.w;
        out << pl.Health;
        out << pl.dir;

        return out;
    }

    friend QDataStream &operator >>(QDataStream &in, Data &pl)
    {
        QString name;

        in >> name;
        in >> pl.x;
        in >> pl.y;
        in >> pl.dx;
        in >> pl.dy;
        in >> pl.h;
        in >> pl.w;
        in >> pl.Health;
        in >> pl.dir;

        pl.name = name.toStdString();

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
};

#endif // DATA_H
