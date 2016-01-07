#include "player.h"

Player::Player(QHostAddress ip, QString name, float x, float y, float angle, int health, int armor)
{
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

void Player::setWidth(const float w)
{
    this->width = w;
}

void Player::setHeight(const float h)
{
    this->height = h;
}

void Player::setName(const QString name)
{
    if (!name.isEmpty())
        this->name = name;
}

void Player::setIp(const QHostAddress ip)
{
    if (!ip.isNull())
        this->ip = ip;
}

void Player::setX(const float x)
{
    this->x = x;
}

void Player::setY(const float y)
{
    this->y = y;
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
}

void Player::setHealth(const int health)
{
    if (health > 100)
        this->health = 100;
    else if (health < 0)
        this->health = 0;
    else
        this->health = health;
}

void Player::setArmor(const int armor)
{
    if (armor > 100)
        this->armor = 100;
    else if (armor < 0)
        this->armor = 0;
    else
        this->armor = armor;
}
