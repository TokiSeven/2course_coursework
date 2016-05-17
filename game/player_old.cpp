#include "player_old.h"

Player_old::Player_old()
    : QObject()
{
    this->setOnline(true);
    this->setIp(QHostAddress::LocalHost);
    this->setName("Player_old#");
    this->setX(0);
    this->setY(0);
    this->setAngle(0);
    this->setHealth(100);
    this->setArmor(100);
    this->setWidth(50);
    this->setHeight(50);
}

Player_old::Player_old(QHostAddress ip, QString name, float x, float y, float angle, int health, int armor, QObject *parent)
    : QObject(parent)
{
    this->setOnline(true);
    this->setIp(ip);
    this->setName(name);
    this->setX(x);
    this->setY(y);
    this->setAngle(angle);
    this->setHealth(health);
    this->setArmor(armor);
    this->setWidth(50);
    this->setHeight(50);
}

Player_old::Player_old(const Player_old &pl)
    : QObject(pl.parent())
{
    this->setOnline(pl.getOnline());
    this->setIp(pl.getIp());
    this->setName(pl.getName());
    this->setX(pl.getX());
    this->setY(pl.getY());
    this->setAngle(pl.getAngle());
    this->setHealth(pl.getHealth());
    this->setArmor(pl.getArmor());
    this->setWidth(pl.getWidth());
    this->setHeight(pl.getHeight());
}

Player_old::~Player_old()
{
}

void Player_old::setOnline(bool fl)
{
    this->online = fl;
}

void Player_old::setWidth(const float w)
{
    if (w >= 0)
    {
        this->width = w;
        emit changed_update(this);
    }
}

void Player_old::setHeight(const float h)
{
    if (h >= 0)
    {
        this->height = h;
        emit changed_update(this);
    }
}

void Player_old::setName(const QString name)
{
    if (!name.isEmpty())
    {
        this->name = name;
        emit changed_update(this);
    }
}

void Player_old::setIp(const QHostAddress ip)
{
    if (!ip.isNull())
    {
        this->ip = ip;
        emit changed_update(this);
    }
}

void Player_old::setX(const float x)
{
    this->x = x;
    emit changed_update(this);
}

void Player_old::setY(const float y)
{
    this->y = y;
    emit changed_update(this);
}

void Player_old::setAngle(const float angle)
{
    float buff = angle;
    while(buff > 360 || buff < 0)
    {
        if (buff > 360)
            buff -= 360;
        if (buff < 0)
            buff += 360;
    }
    this->angle = buff;
    emit changed_update(this);
}

void Player_old::setHealth(const int health)
{
    if (health > 100)
        this->health = 100;
    else if (health < 0)
        this->health = 0;
    else
        this->health = health;
    emit changed_update(this);
}

void Player_old::setArmor(const int armor)
{
    if (armor > 100)
        this->armor = 100;
    else if (armor < 0)
        this->armor = 0;
    else
        this->armor = armor;
    emit changed_update(this);
}

Player_old Player_old::operator =(const Player_old &pl)
{
    this->setHeight(pl.getHeight());
    this->setWidth(pl.getWidth());
    this->setOnline(pl.getOnline());
    //(*this)(pl);
    this->operator ()(pl);
    return (*this);
}

void Player_old::operator ()(const Player_old pl)
{
    this->operator ()(pl.getName(), pl.getX(), pl.getY(), pl.getAngle(), pl.getHealth(), pl.getArmor());
}

void Player_old::operator ()(QString name, float x, float y, float angle, int health, int armor)
{
    //this->setIp(ip);
    this->setName(name);
    this->setX(x);
    this->setY(y);
    this->setAngle(angle);
    this->setHealth(health);
    this->setArmor(armor);
}

bool Player_old::operator ==(const Player_old Player_old)
{
    return (this->getName() == Player_old.getName() && this->getIp() == Player_old.getIp()) ? true : false;
}
