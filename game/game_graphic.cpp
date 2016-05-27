#include "game_graphic.h"

Game_graphic::Game_graphic(Container *cont, QObject *parent)//constructor, set size of window and it's name
    : QObject(parent)
{
    qDebug() << QString("Game_graphic-->> ") + "Created.";
    this->cont = cont;

    this->windowHeight = 280;
    this->windowWidth = 450;
    this->windowName = "Anime Fighting v7.0";

    this->TICK.setInterval(10);
    connect(&TICK, SIGNAL(timeout()), this, SLOT(slot_main_cycle()));

    Ichigo = NULL;
    view = NULL;

    wasStarted = false;
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

Game_graphic::~Game_graphic()//destructor
{
    if (Ichigo)
        delete Ichigo;
    if (view)
        delete view;
    entities.clear();
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::initialization()
{
    view = new View(FloatRect(0, 0, this->windowWidth, this->windowHeight)); // камера

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

    music.openFromFile("files/bg.wav");
    music.play();
    music.setVolume(20);

    o = false;
    //spell = false;
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::updatePlayersAll()
{
    slot_update();
    cont->updatePlayer(Ichigo->toData());
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::main_cycle()//started every cycle of game
{
    if (Ichigo->Health <= 0)
        Ichigo->Health = 100, Ichigo->x = 300, Ichigo->y = 100;
    float time = clock.getElapsedTime().asMicroseconds(); // run time of 1 clock cycle
    clock.restart();

    time = time / 500;  // speed of the game

    if (time > 40) time = 40;

    // >>>------------------------------------->>>FOR KEYBOARD<<<--------------------------------------<<<
    // >>>----------------------------------------->>>BEGIN<<<-----------------------------------------<<<
    QString keyPress;
    keyPress.clear();
    if (Keyboard::isKeyPressed(Keyboard::Left)) Ichigo->key["L"]=true, keyPress = "L";
    if (Keyboard::isKeyPressed(Keyboard::Right)) Ichigo->key["R"]=true, keyPress = "R";
    if (Keyboard::isKeyPressed(Keyboard::Up)) Ichigo->key["Up"]=true, keyPress = "Up";
    if (Keyboard::isKeyPressed(Keyboard::Down)) Ichigo->key["Down"]=true, keyPress = "Down";
    if (Keyboard::isKeyPressed(Keyboard::Space)) Ichigo->key["Space"]=true, keyPress = "Space";
    if (Keyboard::isKeyPressed(Keyboard::C)) Ichigo->key["C"]=true, keyPress = "C";
    if (Keyboard::isKeyPressed(Keyboard::V)) Ichigo->key["V"]=true, keyPress = "V";
    if (Keyboard::isKeyPressed(Keyboard::B)) Ichigo->key["B"]=true, keyPress = "B";
    if (!keyPress.isEmpty())
        emit signal_keyPressed(keyPress);
    // >>>------------------------------------->>>FOR KEYBOARD<<<--------------------------------------<<<
    // >>>---------------------------------------->>>FINISH<<<-----------------------------------------<<<

    //    if(Keyboard::isKeyPressed(Keyboard::O))
    //        if(!o)
    //        {
    //            entities.push_back(new PLAYER(anim, lvl, 700, 500,"Player",0.0,0.0,100,"stay",0,anim.animList[anim.currentAnim].frames[anim.animList[anim.currentAnim].currentFrame].width,anim.animList[anim.currentAnim].frames[anim.animList[anim.currentAnim].currentFrame].height));
    //            o=true;
    //        }

    if(Ichigo->anim.animList["spell"].currentFrame >= 6 && Ichigo->anim.animList["spell"].currentFrame < 6.1 && !Ichigo->spell2)
    {
        entities.push_back(new Spell(anim2,lvl,Ichigo->x+25,Ichigo->y-60,Ichigo->dir,"Spell", 0.3, 0.0, 10, "move",anim2.animList[anim2.currentAnim].frames[anim2.animList[anim2.currentAnim].currentFrame].width,anim2.animList[anim2.currentAnim].frames[anim2.animList[anim2.currentAnim].currentFrame].height)); // добавление способности в массив объектов
        Ichigo->spell2 = true;
    }
    if(Ichigo->anim.animList["spell"].currentFrame > 6.1)
        Ichigo->spell2 = false;

    for (it = entities.begin(); it != entities.end(); it++)
    {
        Entity *e = *it;
        if (e->getType() == QString("Player"))
        {
            PLAYER *en = (PLAYER*)e;
            if(en->anim.animList["spell"].currentFrame >= 6 && en->anim.animList["spell"].currentFrame < 6.1 && !en->spell2)
            {
                entities.push_back(new Spell(anim2,
                                             lvl,
                                             en->x+25,
                                             en->y-60,
                                             en->dir,
                                             "Spell",
                                             0.3,
                                             0.0,
                                             10,
                                             "move",
                                             anim2.animList[anim2.currentAnim].frames[anim2.animList[anim2.currentAnim].currentFrame].width,
                        anim2.animList[anim2.currentAnim].frames[anim2.animList[anim2.currentAnim].currentFrame].height
                        ));
                en->spell2 = true;
            }
            if(en->anim.animList["spell"].currentFrame > 6.1)
                en->spell2 = false;
        }
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
        else
        {
            if (b->getType() == "Player")
                if (((PLAYER*)b)->anim.animList["spell"].currentFrame > 6.1)
                    ((PLAYER*)b)->spell2 = false;
            it++;
        }
    }


    Ichigo->update(time); // player's update
    healthBar.update(Ichigo->Health); // healthbar's update

    // >>>--------------------->>>INTERACTION OF OBJECTS<<<---------------------<<<
    // >>>----------------------------->>>START<<<------------------------------<<<
    for(it=entities.begin();it!=entities.end();it++)
    {
        // враги
        if ((*it)->getType()==QString("Player"))
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
                        if(spell->getRect().intersects(Ichigo->getRect())) // если способность взаимодействует с врагом
                        { // то пропадает и отнимает жизни
                            spell->Health=0;
                            Ichigo->Health-=20;
                            Ichigo->hit = true;
                            std::cout << spell->dir;
                            if (spell->dir)
                                Ichigo->x-=50;
                            else
                                Ichigo->x+=50;
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

    // >>>--------------------->>>INTERACTION OF OBJECTS<<<---------------------<<<
    // >>>---------------------------->>>FINISH<<<------------------------------<<<

    // >>>--------------------->>>working with the screen<<<---------------------<<<
    // >>>----------------------------->>>START<<<-------------------------------<<<

    view->setCenter(Ichigo->x,Ichigo->y-50); // set the camera
    window->setView(*view);
    // set background's position
    background.setPosition(view->getCenter());

    // >>>--------------------->>>working with the screen<<<---------------------<<<
    // >>>---------------------------->>>FINISH<<<-------------------------------<<<

}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

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

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::events(sf::Event &event)//when something was done (for example, pressed key or mouse)
{
    if (event.type == sf::Event::Closed)
    {
        emit signal_game_closed();
        this->slot_close();
    }
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::game_start()//main function of game
{
    wasStarted = true;

    //sf::RenderWindow window(sf::VideoMode(this->windowWidth, this->windowHeight), this->windowName.toStdString().c_str());
    this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), this->windowName.toStdString().c_str());

    this->initialization();

    this->TICK.start();
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::slot_update()
{
    int size = cont->getPlayer_all().size();

    if (size != this->getSizeOfEnemies())
    {
        clearEnemies();
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
    else
    {
        for (int i = 0; i < size; i++)
        {
            Entity* en = findEnemy(cont->getPlayer_all()[i].getName());
            if (en)
                ((Data*)en)->operator =(cont->getPlayer_all()[i]);
        }
    }
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::slot_game_start()
{
    this->game_start();
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::slot_close()
{
    this->TICK.stop();
    entities.clear();
    music.stop();
    if (wasStarted)
    {
        this->window->close();
        delete window;
        delete Ichigo;
        delete view;
    }
    wasStarted = false;
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::slot_keyPress(QString name, QString key)
{
    Entity *ent = findEnemy(name);
    if (ent != NULL)
    {
        PLAYER *en = (PLAYER*)ent;
        en->key[key.toStdString().c_str()] = true;
    }
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::slot_main_cycle()
{
    if (wasStarted)
    {
        if (window->isOpen())
        {
            this->updatePlayersAll();

            sf::Event event;
            while (window->pollEvent(event))
            {
                events(event);
                if (!wasStarted)
                    return;
            }

            this->main_cycle();

            window->clear();
            this->draw();
            window->display();
        }
    }
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

void Game_graphic::clearEnemies()
{
    for(it=entities.begin();it!=entities.end();)
    {
        Entity *b = *it;
        if (b->getType() == QString("Player") && b->getName() != cont->getPlayer_current().getName())
        {
            it  = entities.erase(it);
            delete b;
        }
        else
            it++;
    }
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

int Game_graphic::getSizeOfEnemies()
{
    int size = 0;
    for (it = entities.begin(); it != entities.end(); it++)
    {
        Entity *b = *it;
        if (b->getType() == QString("Player") && b->getName() != cont->getPlayer_current().getName())
            size++;
    }
    return size;
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================

Entity *Game_graphic::findEnemy(QString name)
{
    Entity* temp = NULL;
    for (it = entities.begin(); it != entities.end() && !temp; it++)
    {
        Entity *b = *it;
        if (b->getType() == QString("Player") && b->getName() == name)
            temp = b;
    }
    return temp;
}

// ====================================================================================
// ====================================================================================
// ====================================================================================
// ====================================================================================
