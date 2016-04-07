#include "game_graphic.h"

Game_graphic::Game_graphic(Container *cont)//constructor, set size of window and it's name
{
    this->cont = cont;

    this->windowHeight = 400;
    this->windowWidth = 600;
    this->windowName = "NoName";

    connect(cont, SIGNAL(signal_update_current()), this, SLOT(slot_update()));
}

Game_graphic::~Game_graphic()//destructor
{
    //emit signal_closed();
    //    if (this)
    //        delete this;
}

void Game_graphic::initialization()
{
    pl_all.clear();

    int size = cont->getPlayer_all().size();
    float width = cont->getPlayer_current().getWidth();
    float height = cont->getPlayer_current().getHeight();

    //for current player
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color(100, 100, 100));
    rect.setPosition(cont->getPlayer_current().getX(), cont->getPlayer_current().getY());
    pl_current = rect;
    //connect(cont->getPlayer_current(), SIGNAL(changed_position(Player*)), this, SLOT(slot_position(Player*)));

    //for all players
    for(int i = 0; i < size; i++)
    {
        rect.setPosition(cont->getPlayer_all()[i].getX(), cont->getPlayer_all()[i].getY());
        pl_all.append(rect);
    }
}

void Game_graphic::main_cycle()//started every cycle of game
{
}

void Game_graphic::draw()//draw on the window all that we have
{
    window->draw(pl_current);
    for(int i = 0; i < pl_all.size(); i++)
        window->draw(pl_all[i]);
}

void Game_graphic::events(sf::Event &event)//when something was done (for example, pressed key or mouse)
{
    if (event.type == sf::Event::Closed)
        window->close();
    if (event.type == sf::Event::KeyPressed)
    {
        Player pl(cont->getPlayer_current());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            pl.setX(pl.getX() - 1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            pl.setX(pl.getX() + 1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pl.setY(pl.getY() - 1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            pl.setY(pl.getY() + 1);
        cont->updatePlayer(pl);
        initialization();
    }
}

void Game_graphic::game_start()//main function of game
{
    //sf::RenderWindow window(sf::VideoMode(this->windowWidth, this->windowHeight), this->windowName.toStdString().c_str());
    this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), this->windowName.toStdString().c_str());

    this->initialization();

    while (window->isOpen())
    {
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
void Game_graphic::slot_position(Player player)
{
    int num = cont->getPlayer_all().indexOf(player);
    if (num == -1)//if didn't been finded in all players (it will be yourself)
        this->pl_current.setPosition(cont->getPlayer_current().getX(), cont->getPlayer_current().getY());
    else if (num < cont->getPlayer_all().size())
        this->pl_all[num].setPosition(cont->getPlayer_all()[num].getX(), cont->getPlayer_all()[num].getY());
}

void Game_graphic::slot_update()
{
    initialization();
}

void Game_graphic::slot_game_start()
{
    this->game_start();
}

//================================================================================================
//==========================================SLOTS(FINISH)==========================================
//================================================================================================
