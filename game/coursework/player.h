#ifndef PLAYER_H
#define PLAYER_H

#include "./entity.h"


class PLAYER: public Entity // класс игрока
{
public:
    enum {stay,walk,jump} STATE; // состояния игрока
    bool spell, hit, cattack, vattack; // логические переходы
    std::map<std::string,bool> key; // нажатие клавиш
    SoundBuffer Abuf, A2buf, HITbuf, Jbuf;
    Sound A, A2, HIT, J;

    PLAYER(AnimationManager &a, Level &lev,int x,int y, std::string name, float dx, float dy, int health, std::string first_anim):Entity(a,x,y,name,dx,dy,health,first_anim)
    {
        STATE=stay;
        hit=false, spell=false, cattack=false, vattack=false;
        obj = lev.GetAllObjects(); // массив объектов
        Abuf.loadFromFile("files/attack.wav");
        A.setBuffer(Abuf);
        A2buf.loadFromFile("files/attack2.wav");
        A2.setBuffer(A2buf);
        HITbuf.loadFromFile("files/hit.wav");
        HIT.setBuffer(HITbuf);
        Jbuf.loadFromFile("files/jump.ogg");
        J.setBuffer(Jbuf);
    }

    void Keyboard() // условия нажатия клавиш
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
            if(STATE==stay || STATE==walk){ dy=-0.41;STATE=jump; anim.play("jump");}
        }

        if (key["Space"]) // специальное умение
        {
            dx=0;
            if(!spell)
            {
                anim.animList["spell"].currentFrame = 0;
                spell = true;
                anim.play("spell");
            }
        }

        if (key["C"]) // обычная атака
        {
            dx=0;
            if(!cattack)
            {
                A.play();
                anim.animList["cattack"].currentFrame = 0;
                anim.animList["cforwardattack"].currentFrame = 0;
                anim.animList["cjumpattack"].currentFrame = 0;
                cattack=true;
                anim.play("cattack");
                anim.play("cforwardattack");
                anim.play("cjumpattack");
            }
        }

        if (key["V"]) // особая атака
        {
            dx=0;
            if(!vattack)
            {
                A2.play();
                anim.animList["vattack"].currentFrame = 0;
                anim.animList["vforwardattack"].currentFrame = 0;
                anim.animList["vjumpattack"].currentFrame = 0;
                vattack=true;
                anim.play("vattack");
                anim.play("vforwardattack");
                anim.play("vjumpattack");
            }
        }

        /////////////////////если клавиша отпущена///////////////////////////
        if (!(key["R"] || key["L"]))
        {
            dx=0;
            if (STATE==walk) STATE=stay;
        }

        if (!key["Space"])
        {
            spell = false;
        }

        if (!key["C"])
        {
            cattack=false;
        }

        if (!key["V"])
        {
            vattack=false;
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
            anim.set("cattack");
            if(!anim.animList["cattack"].isPlaying)
                anim.set("stay");
            if (STATE==walk) anim.set("cforwardattack");
            if(!anim.animList["cforwardattack"].isPlaying)
                anim.set("stay");
            if (STATE==jump) anim.set("cjumpattack");
            if(!anim.animList["cjumpattack"].isPlaying)
                anim.set("jump");
        }

        if (vattack)
        {
            anim.set("vattack");
            if(!anim.animList["vattack"].isPlaying)
                anim.set("stay");
            if (STATE==walk) anim.set("vforwardattack");
            if(!anim.animList["vforwardattack"].isPlaying)
                anim.set("stay");
            if (STATE==jump) anim.set("vjumpattack");
            if(!anim.animList["vjumpattack"].isPlaying)
                anim.set("jump");
        }

        if (hit)
        {
            timer+=time;
            if (timer>1000)
            {
                hit=false;
                timer=0;
                HIT.play();
            }
            anim.set("hit");
        }      

        if (dir) anim.flip(); // если зеркальное отображение

        anim.tick(time); // функция анимации
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
