#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "./animation.h"
#include "./level.h"


using namespace sf;

class Entity // класс объектов
{
public:
    float x,y,dx,dy,w,h; // координаты, скорость, ширина, высота
    AnimationManager anim; // набор анимаций
    std::vector<Object> obj; // массив объектов
    bool life, dir; // существование объекта, направление
    float timer; // таймер
    std::string name; // имя объекта
    int Health; // здоровье

    Entity(AnimationManager &A,int X, int Y,std::string NAME, float DX, float DY, int HEALTH, std::string FIRST_ANIM)
    {
        anim = A;
        x = X;
        y = Y;
        dir = 0;
        name = NAME;
        anim.set(FIRST_ANIM);
        w = anim.animList[anim.currentAnim].frames[0].width;
        h = anim.animList[anim.currentAnim].frames[0].height;
        dx = DX;
        dy = DY;
        Health = HEALTH;
        life=true;
        timer=0;
    }

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
