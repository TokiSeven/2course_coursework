#include "game_graphic.h"

Game_graphic::Game_graphic(Container *cont, QObject *parent)//constructor, set size of window and it's name
    : QObject(parent)
{
    qDebug() << QString("Game_graphic-->> ") + "Created.";
    this->cont = cont;

    this->windowHeight = 280;
    this->windowWidth = 450;
    this->windowName = "Anime Fighting v 5.0";

    //connect(cont, SIGNAL(signal_update_all()), this, SLOT(slot_update()));
}

Game_graphic::~Game_graphic()//destructor
{
    //emit signal_closed();
    //    if (this)
    //        delete this;
}

void Game_graphic::initialization()
{
    view = new View(FloatRect(0, 0, 450, 280)); // камера

    lvl.LoadFromFile("files/map.tmx");

    bg.loadFromFile("files/images/bg.png");
    ichigo_t.loadFromFile("files/images/ichigo1.png");

    anim.loadFromXML("files/anim_Ichigo.xml",ichigo_t);

    anim.animList["jump"].loop = 0;
    anim.animList["cattack"].loop = 0;
    anim.animList["cjumpattack"].loop = 0;
    anim.animList["spell"].loop = 0;

    anim2.loadFromXML("files/anim_getsuga.xml",ichigo_t);
    anim2.animList["explode"].loop = 0;

    background.setTexture(bg);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);

    Ichigo = new PLAYER(anim, lvl, 300, 100,cont->getPlayer_current().name,0.0,0.0,100,"stay",0,anim.animList[anim.currentAnim].frames[anim.animList[anim.currentAnim].currentFrame].width,anim.animList[anim.currentAnim].frames[anim.animList[anim.currentAnim].currentFrame].height);
    cont->updatePlayer(Ichigo->toData());

    music.openFromFile("files/bg.wav");
    music.play();
    music.setVolume(20);

    o = false;
    spell = false;

}

void Game_graphic::updatePlayersAll()
{
    slot_update();
}

void Game_graphic::main_cycle()//started every cycle of game
{
    float time = clock.getElapsedTime().asMicroseconds(); // время выполнения за 1 такт процессора
    clock.restart();

    time = time / 500;  // здесь регулируем скорость игры

    if (time > 40) time = 40;

    // нажатие клавиш
    if (Keyboard::isKeyPressed(Keyboard::Left)) Ichigo->key["L"]=true;
    if (Keyboard::isKeyPressed(Keyboard::Right)) Ichigo->key["R"]=true;
    if (Keyboard::isKeyPressed(Keyboard::Up)) Ichigo->key["Up"]=true;
    if (Keyboard::isKeyPressed(Keyboard::Down)) Ichigo->key["Down"]=true;
    if (Keyboard::isKeyPressed(Keyboard::Space)) Ichigo->key["Space"]=true;
    if (Keyboard::isKeyPressed(Keyboard::C)) Ichigo->key["C"]=true;
    if (Keyboard::isKeyPressed(Keyboard::V)) Ichigo->key["V"]=true;
    if (Keyboard::isKeyPressed(Keyboard::B)) Ichigo->key["B"]=true;

    if(Keyboard::isKeyPressed(Keyboard::O))
        if(!o)
        {
            entities.push_back(new PLAYER(anim, lvl, 700, 500,"Player",0.0,0.0,100,"stay",0,anim.animList[anim.currentAnim].frames[anim.animList[anim.currentAnim].currentFrame].width,anim.animList[anim.currentAnim].frames[anim.animList[anim.currentAnim].currentFrame].height));
            o=true;
        }

    if(Ichigo->anim.animList["spell"].currentFrame >= 6 && Ichigo->anim.animList["spell"].currentFrame < 6.1 && !spell)
    {
        entities.push_back(new Spell(anim2,lvl,Ichigo->x+25,Ichigo->y-60,Ichigo->dir,"Spell", 0.3, 0.0, 10, "move",anim2.animList[anim2.currentAnim].frames[anim2.animList[anim2.currentAnim].currentFrame].width,anim2.animList[anim2.currentAnim].frames[anim2.animList[anim2.currentAnim].currentFrame].height)); // добавление способности в массив объектов
        spell = true;
    }
    if(Ichigo->anim.animList["spell"].currentFrame > 6.1)
        spell = false;


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


    Ichigo->update(time); // обновление игрока
    healthBar.update(Ichigo->Health); // обновление полоски здоровья

    for(it=entities.begin();it!=entities.end();it++) // взаимодействие объектов
    {
        // враги
        if ((*it)->getType()=="Player")
        {
            Entity *pl = *it;
            PLAYER *player = (PLAYER*)pl;

            if (player->Health<=0) continue;

            // если объекты пересекаются
            if  (Ichigo->getRect().intersects(player->getRect()))
            { // и у персонажа проигрывается анимация атаки
                if (Ichigo->anim.currentAnim == "cattack" || Ichigo->anim.currentAnim == "cjumpattack")
                    if((Ichigo->x < player->x && Ichigo->dir == 0) ||(Ichigo->x >= player->x && Ichigo->dir == 1))
                    { // то раним врага
                        player->hit = true;
                        player->Health-=5;
                        if (Ichigo->dir)
                            player->x-=50;
                        else
                            player->x+=50;
                    }
                if (player->anim.currentAnim == "cattack" || player->anim.currentAnim == "0cjumpattack")
                    if((player->x < Ichigo->x && player->dir == 0) ||(player->x >= Ichigo->x && player->dir == 1))
                    { // иначе раним игрока
                        Ichigo->Health-=5;
                        Ichigo->hit=true;
                        if (player->dir)
                            Ichigo->x+=50;
                        else
                            Ichigo->x-=50;
                    }
            }


            // способности
            for (std::list<Entity*>::iterator it2=entities.begin(); it2!=entities.end(); it2++)
            {
                Entity *spell = *it2;
                if (spell->getType()=="Spell")
                    if (spell->Health>0)
                    {
                        if(spell->getRect().intersects(player->getRect())) // если способность взаимодействует с врагом
                        { // то пропадает и отнимает жизни
                            spell->Health=0;
                            player->Health-=20;
                            player->hit = true;
                            std::cout << spell->dir;
                            if (spell->dir)
                                player->x-=50;
                            else
                                player->x+=50;
                        }
                        for (std::list<Entity*>::iterator it3=entities.begin(); it3!=entities.end(); it3++)
                        {
                            Entity *spell2 = *it3;
                            if(spell2->getType()=="Spell")
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



    // ///////////////////отображаем на экран/////////////////////
    view->setCenter(Ichigo->x,Ichigo->y-50); // установка камеры
    window->setView(*view);
    // отрисовка фона и карты
    background.setPosition(view->getCenter());
}

void Game_graphic::draw()//draw on the window all that we have
{
    window->draw(background);

    lvl.Draw(*window);

    // отрисовка объектов
    for(it=entities.begin();it!=entities.end();it++)
        (*it)->draw(*window);

    // отрисовка игрока и полоски здоровья
    Ichigo->draw(*window);
    healthBar.draw(*window);
}

void Game_graphic::events(sf::Event &event)//when something was done (for example, pressed key or mouse)
{
    if (event.type == sf::Event::Closed)
    {
        emit signal_game_closed();
        window->close();
    }
    //    if (event.type == sf::Event::KeyPressed)
    //    {
    //        Player_old pl(cont->getPlayer_current());
    //        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //            pl.setX(pl.getX() - 1);
    //        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    //            pl.setX(pl.getX() + 1);
    //        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //            pl.setY(pl.getY() - 1);
    //        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //            pl.setY(pl.getY() + 1);
    //        cont->updatePlayer(pl);
    //    }
}

void Game_graphic::game_start()//main function of game
{
    //sf::RenderWindow window(sf::VideoMode(this->windowWidth, this->windowHeight), this->windowName.toStdString().c_str());
    this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), this->windowName.toStdString().c_str());

    this->initialization();

    while (window->isOpen())
    {
        this->updatePlayersAll();

        sf::Event event;
        while (window->pollEvent(event))
        {
            events(event);
        }

        this->main_cycle();

        window->clear();
        this->draw();
        window->display();
    }
    emit signal_game_closed();
}

//================================================================================================
//==========================================SLOTS(BEGIN)==========================================
//================================================================================================
void Game_graphic::slot_position(Data player)
{
//    int num = cont->getPlayer_all().indexOf(player);
//    if (num == -1)//if didn't been finded in all players (it will be yourself)
//        this->pl_current.setPosition(cont->getPlayer_current().getX(), cont->getPlayer_current().getY());
//    else if (num < cont->getPlayer_all().size())
//        this->pl_all[num].setPosition(cont->getPlayer_all()[num].getX(), cont->getPlayer_all()[num].getY());
}

void Game_graphic::slot_update()
{
    clearEnemies();
    int size = cont->getPlayer_all().size();
    for (int i = 0; i < size; i++)
    {
        Data temp;
        temp = cont->getPlayer_all()[i];
        entities.push_back(new PLAYER(anim,
                                      lvl,
                                      temp.x,
                                      temp.y,
                                      temp.name,
                                      temp.dx,
                                      temp.dy,
                                      temp.Health,
                                      "Stay",
                                      temp.dir,
                                      temp.w,
                                      temp.h)
                           );
    }
}

void Game_graphic::slot_game_start()
{
    this->game_start();
}

void Game_graphic::slot_close()
{
    emit signal_game_closed();
    this->window->close();
}

void Game_graphic::clearEnemies()
{
    for(it=entities.begin();it!=entities.end();)
    {
        Entity *b = *it;
        if (b->getType() == "Player" && b->getName() != cont->getPlayer_current().getName())
        {
            it  = entities.erase(it);
            delete b;
        }
        else
            it++;
    }
}

//================================================================================================
//==========================================SLOTS(FINISH)==========================================
//================================================================================================
