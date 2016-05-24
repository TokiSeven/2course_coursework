#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "animation.h"
#include "level.h"
#include "data.h"


using namespace sf;

class Entity
        : public Data// класс объектов
{
public:
    AnimationManager anim; // набор анимаций
    std::vector<Object> obj; // массив объектов
    QString type;

    Entity(AnimationManager &A,int X, int Y,std::string NAME, float DX, float DY, int HEALTH, std::string FIRST_ANIM,bool DIR, float W, float H)
        : Data(X, Y, NAME, DX, DY, HEALTH, DIR, W, H)
    {
        this->type = "Entity";
        anim = A;
        anim.set(FIRST_ANIM);
    }

    QString getType()const{return this->type;}
    virtual void update(float time) = 0; // функция обновления

    void draw(RenderWindow &window) // функция отрисовки
    {
        anim.draw(window,x,y+h);
    }

    FloatRect getRect() // получение взаимодействующего прямоугольника
    {
        return FloatRect(x,y,w,h);
    }

};


#endif // ENTITY_H
