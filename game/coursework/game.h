#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "./level.h"
#include "./animation.h"
#include "./entity.h"
#include "./spell.h"
#include "./player.h"
#include "./healthbar.h"
using namespace sf;


void RunGame()
{
    ///////////// инициализация ///////////////////////////
    RenderWindow window(VideoMode(450, 280), "The Game!"); // окно

    View view(FloatRect(0, 0, 450, 280)); // камера

    Level lvl; // карта
    lvl.LoadFromFile("files/map.tmx");
    //qrc:/sounds/background.mp3

    Texture ichigo_t, bg; // текстуры
    bg.loadFromFile("files/images/bg.png");
    ichigo_t.loadFromFile("files/images/ichigo1.png");


    AnimationManager anim; // анимации персонажа
    anim.loadFromXML("files/anim_ichigo.xml",ichigo_t);
    anim.animList["jump"].loop = 0;
    anim.animList["cattack"].loop = 0;
    anim.animList["vattack"].loop = 0;
    anim.animList["cforwardattack"].loop = 0;
    anim.animList["vforwardattack"].loop = 0;
    anim.animList["cjumpattack"].loop = 0;
    anim.animList["vjumpattack"].loop = 0;
    anim.animList["spell"].loop = 0;

    AnimationManager anim2; // анимации способности
    anim2.loadFromXML("files/anim_getsuga.xml",ichigo_t);
    anim2.animList["explode"].loop = 0;

    Sprite background(bg); // фон
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);

    std::list<Entity*>  entities; // массив объектов
    std::list<Entity*>::iterator it;

    PLAYER Ichigo(anim, lvl, 300, 100,"Player",0.0,0.0,100,"stay"); // игрок

    HealthBar healthBar; // полоска жизней

    Music music;
    music.openFromFile("files/bg.wav");
    music.play();
    music.setVolume(20);

    bool o = false;

    bool space = false; // проверка одного нажатия

    Clock clock; // часы

    /////////////////// основной цикл  /////////////////////
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); // время выполнения за 1 такт процессора
        clock.restart();

        time = time/500;  // здесь регулируем скорость игры

        if (time > 40) time = 40;

        Event event; // обработка закрытия окна
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // нажатие клавиш
        if (Keyboard::isKeyPressed(Keyboard::Left)) Ichigo.key["L"]=true;
        if (Keyboard::isKeyPressed(Keyboard::Right)) Ichigo.key["R"]=true;
        if (Keyboard::isKeyPressed(Keyboard::Up)) Ichigo.key["Up"]=true;
        if (Keyboard::isKeyPressed(Keyboard::Down)) Ichigo.key["Down"]=true;
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            Ichigo.key["Space"]=true;
            if(Ichigo.anim.animList["spell"].currentFrame >= 6 && Ichigo.anim.animList["spell"].currentFrame < 6.1)
                if(!space) // анимация способности на 6 кадре 1 раз за 1 нажатие на кнопку
                {
                    space = true;
                    entities.push_back(new Spell(anim2,lvl,Ichigo.x+25,Ichigo.y-60,Ichigo.dir,"Spell", 0.3, 0.0, 10, "move")); // добавление способности в массив объектов
                }
        }
        if (!Keyboard::isKeyPressed(Keyboard::Space))
            space = false;
        if (Keyboard::isKeyPressed(Keyboard::C)) Ichigo.key["C"]=true;
        if (Keyboard::isKeyPressed(Keyboard::V)) Ichigo.key["V"]=true;
        if (Keyboard::isKeyPressed(Keyboard::B)) Ichigo.key["B"]=true;

        if(Keyboard::isKeyPressed(Keyboard::O))
            if(!o)
            {
                entities.push_back(new PLAYER(anim, lvl, 700, 500,"Player",0.0,0.0,100,"stay"));
                o=true;
            }

        for(it=entities.begin();it!=entities.end();) // есои объект мертв, то удаляем из массива
        {
            Entity *b = *it;
            b->update(time);
            if (b->life==false)
            {
                it  = entities.erase(it);
                delete b;
            }
            else it++;
        }


        Ichigo.update(time); // обновление игрока
        healthBar.update(Ichigo.Health); // обновление полоски здоровья


        for(it=entities.begin();it!=entities.end();it++) // взаимодействие объектов
        {
            // враги
            if ((*it)->name=="Player")
            {
                Entity *pl = *it;
                PLAYER *player = (PLAYER*)pl;

                if (player->Health<=0) continue;

                if  (Ichigo.getRect().intersects(player->getRect())) // если объекты пересекаются
                { // и у персонажа проигрывается анимация атаки
                    if (Ichigo.anim.isPlaying() && Ichigo.anim.currentAnim != "stay" && Ichigo.anim.currentAnim != "jump" && Ichigo.anim.currentAnim != "spell" && Ichigo.anim.currentAnim != "walk" && Ichigo.anim.currentAnim != "hit")
                    { // то раним врага
                        player->hit = true;
                        player->Health-=5;
                        if (player->dir)
                            player->x+=10;
                        else
                            player->x-=10;
                    }
                    else if (!Ichigo.hit)
                    { // иначе раним игрока
                        Ichigo.Health-=5;
                        Ichigo.hit=true;
                        if (Ichigo.dir)
                            Ichigo.x+=10;
                        else
                            Ichigo.x-=10;
                    }
                }

            // способности
                for (std::list<Entity*>::iterator it2=entities.begin(); it2!=entities.end(); it2++)
                {
                    Entity *spell = *it2;
                    if (spell->name=="Spell")
                        if (spell->Health>0)
                        {
                            if(spell->getRect().intersects(player->getRect())) // если способность взаимодействует с врагом
                             { // то пропадает и отнимает жизни
                                spell->Health=0;
                                player->Health-=5;
                            }
                            for (std::list<Entity*>::iterator it3=entities.begin(); it3!=entities.end(); it3++)
                            {
                                Entity *spell2 = *it3;
                                if(spell2->name=="Spell")
                                    if(spell2->Health>0)
                                        if(spell->getRect() != spell2->getRect()) // если способность взаимодействует со способностью
                                            if(spell->getRect().intersects(spell2->getRect()))
                                            { // то они взаимоуничтожаются
                                                spell->Health=0;
                                                spell2->Health=0;
                                            }
                            }
                        }
                }
            }
        }


        /////////////////////отображаем на экран/////////////////////
        view.setCenter(Ichigo.x,Ichigo.y-50); // установка камеры
        window.setView(view);
        // отрисовка фона и карты
        background.setPosition(view.getCenter());
        window.draw(background);

        lvl.Draw(window);

        // отрисовка объектов
        for(it=entities.begin();it!=entities.end();it++)
            (*it)->draw(window);

        // отрисовка игрока и полоски здоровья
        Ichigo.draw(window);
        healthBar.draw(window);

        window.display();
    }
}

#endif // GAME_H

