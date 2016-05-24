#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class PLAYER: public Entity // класс игрока
{
public:
    enum {stay,walk,jump} STATE; // состояния игрока
    bool spell, hit, cattack, spellPush, cattackPush, jumpPush; // логические переходы
    std::map<std::string,bool> key; // нажатие клавиш
    SoundBuffer Abuf, HITbuf, Jbuf;
    Sound A, HIT, J;

    PLAYER(AnimationManager &a, Level &lev,int x,int y, std::string name, float dx, float dy, int health, std::string first_anim, bool DIR, float W, float H)
        : Entity(a,x,y,name,dx,dy,health,first_anim,DIR,W,H)
    {
        this->type = "Player";
        STATE=stay;
        hit=false, spell=false, cattack=false, spellPush=false, cattackPush=false, jumpPush=false;
        obj = lev.GetAllObjects(); // массив объектов
        Abuf.loadFromFile("files/attack.wav");
        A.setBuffer(Abuf);
        HITbuf.loadFromFile("files/hit.wav");
        HIT.setBuffer(HITbuf);
        Jbuf.loadFromFile("files/jump.ogg");
        J.setBuffer(Jbuf);
    }

    void Keyboard() // условия нажатия клавиш
    {
        if(!spell && !cattack)
        {
            if (key["L"]) // если влево
            {
                dir=1; // направление влево
                dx=-0.1; // скорость -0.1
                if(STATE==stay) STATE=walk; // переход из осстояния stay в walk
            }

            if (key["R"]) // вправо
            {
                dir=0;
                dx=0.1;
                if(STATE==stay) STATE=walk;
            }

            if (key["Up"]) // прыжок
            {
                if((STATE==stay || STATE==walk) && !jumpPush)
                {
                    dy=-0.41;
                    STATE=jump;
                    anim.play("jump");
                    jumpPush = true;
                }
            }

            if (key["Space"]) // специальное умение
            {
                if(!spell && !spellPush && STATE!=jump)
                {
                    dx=0;
                    anim.animList["spell"].currentFrame = 0;
                    spell = true;
                    spellPush = true;
                    anim.play("spell");
                }
            }

            if (key["C"]) // атака
            {
                if(!cattack && !cattackPush)
                {
                    A.play();
                    anim.animList["cattack"].currentFrame = 0;
                    anim.animList["cjumpattack"].currentFrame = 0;
                    cattack = true;
                    cattackPush = true;
                    anim.play("cattack");
                    anim.play("cjumpattack");
                }
            }

            // ///////////////////если клавиша отпущена///////////////////////////
            if (!(key["R"] || key["L"]))
            {
                dx=0;
                if (STATE==walk) STATE=stay;
            }

            if (!key["Space"])
            {
                spellPush = false;
            }

            if (!key["C"])
            {
                cattackPush = false;
            }

            if (!key["Up"])
            {
                jumpPush = false;
            }

        }

        key["R"]=key["L"]=key["C"]=key["V"]=key["Up"]=key["Space"]=false;
    }

    void Animation(float time) // функция анимации
    {
        // при определённом состоянии устанавливаем соответсвующую анимацию
        if (STATE==stay) anim.set("stay");
        if (STATE==walk) anim.set("walk");
        if (STATE==jump)
        {
            J.play();
            anim.set("jump");
        }

        if (spell)
        {
            anim.set("spell");
            if(!anim.animList["spell"].isPlaying)
                anim.set("stay");
        }

        if (cattack)
        {
            if (STATE==jump)
                anim.set("cjumpattack");
            else
            {
                dx=0;
                anim.set("cattack");
            }
            if(!anim.animList["cattack"].isPlaying)
                anim.set("stay");
            if(!anim.animList["cjumpattack"].isPlaying)
                anim.set("jump");
        }

        if (hit)
        {
            timer+=time;
            if (timer>600)
            {
                hit=false;
                timer=0;
                HIT.play();
            }
            anim.set("hit");
        }

        if (dir) anim.flip(); // если зеркальное отображение

        if(anim.tick(time) == false)
        {
            spell = false;
            cattack = false;
        }
    }

    void update(float time) // функция обновления
    {
        Keyboard(); // обработка нажатий клавиш

        Animation(time); // функция анимации

        // вычисление координат
        dy+=0.0005*time;

        x+=dx*time;
        Collision(0); // функция обработки столкновений

        y+=dy*time;
        Collision(1);
    }

    void Collision(int num) // функция обработки столкновений
    {
        for (int i=0;i<obj.size();i++)
            if (getRect().intersects(obj[i].rect)) // если наш спрайт пересекается с каким-либо объектом
            {
                if (obj[i].name=="solid") // если такой объект - solid
                {
                    // столкновения по y
                    if (dy>0 && num==1)	{ y = obj[i].rect.top -  h;  dy=0;   STATE=stay;}
                    if (dy<0 && num==1)	{ y = obj[i].rect.top + obj[i].rect.height ;   dy=0;}
                    // столкновения по x
                    if (dx>0 && num==0)	{ x =  obj[i].rect.left -  w; }
                    if (dx<0 && num==0)	{ x =  obj[i].rect.left + obj[i].rect.width ;}
                }

            }
    }

};


#endif // PLAYER_H
