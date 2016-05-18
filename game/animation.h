#ifndef ANIMATION_H
#define ANIMATION_H

#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"
#include <SFML/Graphics.hpp>
#include <QDebug>

using namespace sf;

class Animation // класс анимации
{
public:
    std::vector<IntRect> frames, frames_flip; // кадры
    float currentFrame, speed; // текущий кадр и скорость анимации
    bool loop, flip, isPlaying;   // loop показвает зациклена ли анимация. Например анимация взрыва должна проиграться один раз и остановиться, loop=false
    // flip зеркальное отображение, isPlaying проигрывается ли анимация
    Sprite sprite; // спрайт

    Animation()
    {
        currentFrame = 0;
        isPlaying=true;
        flip=false;
        loop=true;
    }

    bool tick(float time) // сама функция анимации со входным параметром - временем
    {
        if (!isPlaying) return isPlaying; // выход если не проигрывается

        currentFrame += speed * time; // смена кадров

        if (currentFrame > frames.size()) // если анимация проиграна, возвращаемся в начало
        {
            currentFrame -= frames.size();
            if (!loop) // если анимация не зациклена
            {
                isPlaying=false;
                return isPlaying;
            }
        }

        int i = currentFrame;
        sprite.setOrigin(0,frames[i].height); // смена точки отсчёта координат
        sprite.setTextureRect(frames[i]); // наложение кадров на текстуру
        if (flip) sprite.setTextureRect(frames_flip[i]); // зеркальное наложение
        return isPlaying;
    }
};




class AnimationManager // класс набора анимаций
{

public:
    std::string currentAnim; // текущая анимация
    std::map<std::string, Animation> animList; // список анимаций

    AnimationManager()
    {

    }

    ~AnimationManager()
    {
        animList.clear();
    }

    //создание анимаций вручную
    void create(std::string name, Texture &texture, int x, int y, int w, int h, int count, float speed, int step=0, bool Loop=true)
    {
        Animation a;
        a.speed = speed;
        a.loop = Loop;
        a.sprite.setTexture(texture);
        a.sprite.setOrigin(0,h);

        for (int i=0;i<count;i++)
        {
            a.frames.push_back(IntRect(x+i*step, y, w, h));
            a.frames_flip.push_back(IntRect(x+i*step+w, y, -w, h));
        }
        animList[name] = a;
        currentAnim = name;
    }

    //загрузка из файла XML
    void loadFromXML(std::string fileName,Texture &t)
    {
        TiXmlDocument animFile(fileName.c_str());

        animFile.LoadFile();

        TiXmlElement *head;
        head = animFile.FirstChildElement("sprites");

        TiXmlElement *animElement;
        animElement = head->FirstChildElement("animation");
        while(animElement)
        {
            Animation anim;
            currentAnim = animElement->Attribute("title");
            int delay = atoi(animElement->Attribute("delay"));
            anim.speed = 1.0/delay; anim.sprite.setTexture(t);

            TiXmlElement *cut;
            cut = animElement->FirstChildElement("cut");
            while (cut)
            {
                int x = atoi(cut->Attribute("x"));
                int y = atoi(cut->Attribute("y"));
                int w = atoi(cut->Attribute("w"));
                int h = atoi(cut->Attribute("h"));

                anim.frames.push_back( IntRect(x,y,w,h) );
                anim.frames_flip.push_back( IntRect(x+w,y,-w,h)  );
                cut = cut->NextSiblingElement("cut");
            }

            anim.sprite.setOrigin(0,anim.frames[0].height);

            animList[currentAnim] = anim;
            animElement = animElement->NextSiblingElement("animation");
        }
    }

    void set(std::string name) // установка анимации
    {
        currentAnim = name;
        animList[currentAnim].flip=0;
    }

    void draw(RenderWindow &window,int x=0, int y=0) // отрисовка анимации
    {
        animList[currentAnim].sprite.setPosition(x,y);
        window.draw(animList[currentAnim].sprite);
    }

    // функции управления анимациями
    void flip(bool b=1)
    {
        animList[currentAnim].flip = b;
    }

    bool tick(float time)
    {
        return animList[currentAnim].tick(time);
    }

    void pause()
    {
        animList[currentAnim].isPlaying=false;
    }

    void play()
    {
        animList[currentAnim].isPlaying=true;
    }

    void play(std::string name)
    {
        animList[name].isPlaying=true;
    }

    bool isPlaying()
    {
        return animList[currentAnim].isPlaying;
    }

};

#endif // ANIMATION_H
