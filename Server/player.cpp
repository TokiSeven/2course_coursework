#include "player.h"

Player::Player()
{
    this->setOnline(true);
    this->setIp(QHostAddress::LocalHost);
    this->setName("Player#");
    this->setX(0);
    this->setY(0);
    this->setAngle(0);
    this->setHealth(100);
    this->setArmor(100);
    this->setWidth(10);
    this->setHeight(10);
}

Player::Player(QHostAddress ip, QString name, float x, float y, float angle, int health, int armor, QObject *parent)
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
    this->setWidth(10);
    this->setHeight(10);
}

Player::Player(const Player &pl)
{
    (*this) = pl;
}

Player::~Player()
{
}

void Player::setOnline(bool fl)
{
    this->online = fl;
}

void Player::setWidth(const float w)
{
    if (w >= 0)
    {
        this->width = w;
        emit changed_update(this);
    }
}

void Player::setHeight(const float h)
{
    if (h >= 0)
    {
        this->height = h;
        emit changed_update(this);
    }
}

void Player::setName(const QString name)
{
    if (!name.isEmpty())
    {
        this->name = name;
        emit changed_update(this);
    }
}

void Player::setIp(const QHostAddress ip)
{
    if (!ip.isNull())
    {
        this->ip = ip;
        emit changed_update(this);
    }
}

void Player::setX(const float x)
{
    this->x = x;
    emit changed_update(this);
}

void Player::setY(const float y)
{
    this->y = y;
    emit changed_update(this);
}

void Player::setAngle(const float angle)
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

void Player::setHealth(const int health)
{
    if (health > 100)
        this->health = 100;
    else if (health < 0)
        this->health = 0;
    else
        this->health = health;
    emit changed_update(this);
}

void Player::setArmor(const int armor)
{
    if (armor > 100)
        this->armor = 100;
    else if (armor < 0)
        this->armor = 0;
    else
        this->armor = armor;
    emit changed_update(this);
}

Player Player::operator =(const Player &pl)
{
    this->setHeight(pl.getHeight());
    this->setWidth(pl.getWidth());
    this->setOnline(pl.getOnline());
    (*this)(pl);
    return (*this);
}

Player Player::operator ()(const Player pl)
{
    (*this)(pl.getIp(), pl.getName(), pl.getX(), pl.getY(), pl.getAngle(), pl.getHealth(), pl.getArmor());
    return (*this);
}

Player Player::operator ()(QHostAddress ip, QString name, float x, float y, float angle, int health, int armor)
{
    this->setIp(ip);
    this->setName(name);
    this->setX(x);
    this->setY(y);
    this->setAngle(angle);
    this->setHealth(health);
    this->setArmor(armor);
    return (*this);
}

bool Player::operator ==(const Player player)
{
    return (this->getName() == player.getName() && this->getIp() == player.getIp()) ? true : false;
}
