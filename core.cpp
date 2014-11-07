#include "core.hpp"

int engine::load()
{
    if(!pilka_img.loadFromFile("data/img/ball.png"))
        return 11;
    if(!deska_img.loadFromFile("data/img/palette.png"))
        return 12;
    if(!bonus_img.loadFromFile("data/img/bonus.png"))
        return 13;
    if(!basefont.loadFromFile("data/font.ttf"))
        return 21;
    if(!infofont.loadFromFile("data/font.ttf"))
        return 22;

    srand(time(0));

    player1 = new deska(78,17,500,"Gracz 1");
    if(player1 == NULL)return 31;
    player1->looks.setTexture(deska_img);

    player2 = new deska(78,17,500,"Gracz 2");
    if(player2 == NULL)return 32;
    player2->looks.setTexture(deska_img);
    player2->looks.rotate(180);

    //ball = new pilka(10,10,7.0);
    ball = new pilka(10,10,500);
    if(ball == NULL)return 33;
    ball->looks.setTexture(pilka_img);

    this->go(0,800,600);
    return 0;
}

void engine::go(int fullscreen,int width,int height)
{
    if(fullscreen == 0)
        window = new sf::RenderWindow(sf::VideoMode(width, height), name,sf::Style::Close);
    else
        window = new sf::RenderWindow(sf::VideoMode(width, height), name,sf::Style::Fullscreen);
    window->setFramerateLimit(Framerate);
    Wwidth = window->getSize().x;
    Wheight = window->getSize().y;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape : window->close(); break;
                    case sf::Keyboard::Num1 : this->playthegame(); break;
                    case sf::Keyboard::Num2 : this->playthegame(2); break;
                    default: break;
                }
            }
        }

        window->clear();
        window->display();
    }
}

void engine::playthegame(int players)
{
//#################################################################### ZMIENNE
    int score1=0;
    int score2=0;
    int pause=1;

    sf::Clock cl_main;
    sf::Clock clock_2bonus;
    int bonus_text;
//#################################################################### TEXT EDIT
    sf::Text wynik1;
    sf::Text wynik2;
    wynik1.setFont(basefont);
    wynik1.setPosition(10,Wheight/2 - 20);
    wynik1.setColor(sf::Color::Black);
    wynik1.setString("0");

    wynik2.setFont(basefont);
    wynik2.setPosition(Wwidth - 50,Wheight/2 - 20);
    wynik2.setColor(sf::Color::Black);
    wynik2.setString("0");

    MM = new messageMenager(2,&infofont);
//#################################################################### USTAWIENIE ELEMENTOW
    player1->position.x = Wwidth/2 - (player1->width/2);
    player1->position.y = Wheight-player1->height;
    player2->position.x = Wwidth/2 + (player2->width/2);
    player2->position.y = player2->height;

    if(los() == 0)  //komu przyznac pilke
    {
        //pilka gracza 1
        ball->position.x = player1->position.x+(player1->width/2)-(ball->width/2);
        ball->position.y = Wheight-player1->height-(ball->height*2);
        ball->kierunek_y = 0;
        ball->kierunek_x = los();
    }
    else
    {
        //pilka gracza 2
        ball->position.x = player2->position.x -(player2->width/2)-(ball->width/2);
        ball->position.y = player2->height + ball->height;
        ball->kierunek_y = 1;
        ball->kierunek_x = los();
    }

    //is game running ?
    bool running = true;
//========================================== start ===========================================
//#################################################################### handle Events
    while (window->isOpen() && running == true && score1 < doilu && score2 < doilu)
    {
        sf::Event Zdarzenie;
        while (window->pollEvent(Zdarzenie))
        {
            if(Zdarzenie.type == sf::Event::Closed)
                window->close();
            if(Zdarzenie.type == sf::Event::KeyPressed)
            {
                switch(Zdarzenie.key.code)
                {

                    //PLAYER 1
                    case sf::Keyboard::D : player1->czyprawo = true; break;
                    case sf::Keyboard::A : player1->czylewo = true; break;
                    case sf::Keyboard::S : player1->czyactivate = true; break;

                    //PLAYER 2
                    case sf::Keyboard::Right : player2->czyprawo = true; break;
                    case sf::Keyboard::Left : player2->czylewo = true; break;
                    case sf::Keyboard::Down : player2->czyactivate = true; break;

                    //OPTIONS
                    case sf::Keyboard::Escape : running=false; break;
                    case sf::Keyboard::Space  : pause=0; break;
                    default: break;
                }
            }
            if(Zdarzenie.type == sf::Event::KeyReleased)
            {
                switch(Zdarzenie.key.code)
                {

                    //player 1
                    case sf::Keyboard::D : player1->czyprawo = false; break;
                    case sf::Keyboard::A : player1->czylewo = false; break;

                    //player 2
                    case sf::Keyboard::Right : player2->czyprawo = false; break;
                    case sf::Keyboard::Left : player2->czylewo = false; break;

                    default: break;
                }
            }
        }
//#################################################################### Ustawianie elementow
    //## USTAWIENIE PALETEK ##
    if(player1->czylewo == true)
        player1->position.x = player1->position.x-(player1->speed/FPS);
    if(player1->czyprawo == true)
        player1->position.x = player1->position.x+(player1->speed/FPS);
    if(player1->position.x < 0)player1->position.x = 0;
    if(player1->position.x + player1->width > Wwidth)player1->position.x = Wwidth - player1->width;

    if(players > 1)
    {
        if(player2->czylewo == true)
            player2->position.x = player2->position.x-(player2->speed/FPS);

        if(player2->czyprawo == true)
            player2->position.x = player2->position.x+(player2->speed/FPS);
    }
    else    // Jezeli mniej graczy to komputer aktywny
        CPU();
    if(player2->position.x-player2->width < 0)player2->position.x = player2->width;
    if(player2->position.x > Wwidth)player2->position.x = Wwidth;

    //## USTAWIENIE PILKI ##
    if(pause == 0)
    {
        if(ball->kierunek_x == 0)
            ball->position.x -= ball->kat_odbicia/FPS;
        else
            ball->position.x += ball->kat_odbicia/FPS;
        if(ball->kierunek_y == 0)
            ball->position.y += ball->speed/FPS;
        else
            ball->position.y -= ball->speed/FPS;
    }
    //## USTAWIENIA DOTYCZACE PUNKTACJI ##
    if(ball->position.y <= (-ball->height*2) || ball->position.y >= (Wheight - ball->height + (ball->height*2)))
    {
        pause = 1;
        ball->speed_Up(0);
        ball->odbicie();

        if(ball->position.y <= (-ball->height*2))
        {
            score1++;
            MM->nowa(player1->name+" scored!");
            ball->position.x = player2->position.x - (player2->width/2) - (ball->width/2);
            ball->position.y = player2->height + ball->height;
            wynik1.setString(ToString(score1));
            if(players == 1) pause = 0;
        }
        else
            {
                score2++;
                MM->nowa(player2->name+" scored!");
                ball->position.x = player1->position.x+player1->width/2-ball->width/2;
                ball->position.y = Wheight - player1->height - (ball->height*2);
                wynik2.setString(ToString(score2));
            }
    }
    collisions();   //DETEKCJA KOLIZJI
//#################################################################### Bonus
    if(bonus_pack != NULL)
        if((ball->position.y + ball->height >= bonus_pack->position.y) && (ball->position.y <= bonus_pack->position.y+bonus_pack->height))
            if((ball->position.x+ball->width >= bonus_pack->position.x) && (ball->position.x <= bonus_pack->position.x+bonus_pack->width))
            {
                switch(bonus_pack->bonusID)
                {
                    case 1:
                        if(los() == 0)
                        {
                            score2 = score1;
                            wynik2.setString(ToString(score2));
                        }
                        else
                        {
                            score1 = score2;
                            wynik1.setString(ToString(score1));
                        }
                        MM->nowa("Balance!",3);
                        break;
                    case 3:
                        //ball->odbicie(ball->kat_odbicia);
                        //ball->speed_Up(ball->speed*2);
                        MM->nowa("UltraBALL",3);
                        break;
                    default: MM->nowa("*.: EMPTY CREATE :.",3);
                }
                delete(bonus_pack);
                bonus_pack = NULL;
                clock_2bonus.restart();
            }

    //## Bonus On Board ##
    if(clock_2bonus.getElapsedTime().asSeconds() > 15)
    {
        if(bonus_pack == NULL)
        {
            bonus_text = los(1,7);
            switch(bonus_text)
            {
                case 1: MM->nowa("Finish HIM!",1); break;
                case 2: MM->nowa("Tiny gift 4U",1); break;
                case 3: MM->nowa("Arm yourself!",1); break;
                case 4: MM->nowa("Catch this!",1); break;
                case 5: MM->nowa("Handle this!",1); break;
                case 6: MM->nowa("Crush your enemy!",1); break;
                case 7: MM->nowa("Straigh!",1); break;
            }
            bonus_pack = new bonus(&bonus_img,los(0,6),los(50,Wwidth-70),los(50,Wheight-70));
        }
        else
        {
            delete(bonus_pack);
            bonus_pack = NULL;
        }
        clock_2bonus.restart();
    }
//#################################################################### Drawing
    cl_main.restart();
    ball->looks.setPosition(ball->position.x,ball->position.y);
    player1->looks.setPosition(player1->position.x,player1->position.y);
    player2->looks.setPosition(player2->position.x,player2->position.y);

    //## Draw ##//
    window->clear(sf::Color::White);

    sf::RectangleShape line(sf::Vector2f(Wwidth-120,2));
    line.setFillColor(sf::Color::Black);
    line.setPosition(60,(Wheight/2));
    window->draw(line);

    line.setSize(sf::Vector2f(Wwidth-200,1));
    line.setFillColor(sf::Color::Red);
    line.setPosition(100,(player2->height*3));
    window->draw(line);
    line.setFillColor(sf::Color::Red);
    line.setPosition(100,Wheight - (player1->height*3));
    window->draw(line);
    sf::CircleShape circle(50);
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color::Black);
    circle.setPosition(Wwidth/2-50,Wheight/2-50);
    window->draw(circle);

    window->draw(wynik1);
    window->draw(wynik2);
    window->draw(ball->looks);
    window->draw(player1->looks);
    window->draw(player2->looks);
    if(bonus_pack != NULL)window->draw(bonus_pack->looks);
    MM->wyswietl(window);
    window->display();
    FPS = 1/cl_main.getElapsedTime().asSeconds();
//####################################################################
    }
//========================================== stop ===========================================
    if(score1 == doilu)
    {
        endofgame(player1->name);
    }
    if(score2 == doilu)
    {
        endofgame(player2->name);
    }
    //Reset Menadzera Wiadomosci
    MM->clean();
    delete(MM);
    //Reset pilki
    ball->odbicie();

    //RESETOWANIE STEROWANIA
    player1->czylewo = false;
    player1->czyprawo = false;
    player1->czyactivate = false;
    player2->czylewo = false;
    player2->czyprawo = false;
    player2->czyactivate = false;

    //RESETOWANIE BONUSU
    if(bonus_pack != NULL)
    {
        delete(bonus_pack);
        bonus_pack = NULL;
    }
}

void engine::endofgame(std::string winer)
{
    //## KONFIGURACJA NAPISOW ##//
    sf::Text napis;
    napis.setFont(basefont);
    napis.setCharacterSize(24);
    napis.setPosition(window->getSize().x/2,window->getSize().y/2);
    napis.setColor(sf::Color::Yellow);
    napis.setString(winer+" won!");
    //##########################//
    window->clear(sf::Color::Black);
    window->draw(napis);
    window->display();
    sf::sleep(sf::seconds(3));
}

int engine::los(int min_l,int max_l)
{
    return min_l + rand()%(max_l - min_l + 1);
}

void engine::CPU()
{
    if(ball->kierunek_y == 0)
        {
            if(player2->position.x - (player2->width/2) > (Wwidth/2))
                player2->position.x = player2->position.x - (player2->speed/FPS);
            if(player2->position.x - (player2->width/2) < (Wwidth/2))
                player2->position.x = player2->position.x + (player2->speed/FPS);
        }
        else
        {
            if(player2->position.x - (player2->width/2) < ball->position.x)
                player2->position.x = player2->position.x + (player2->speed/FPS);
            if(player2->position.x - (player2->width/2) > ball->position.x)
                player2->position.x = player2->position.x - (player2->speed/FPS);
        }
}

void engine::collisions()
{
    //pilka o scianki
    if(ball->position.x > (Wwidth-ball->width))
    {
        ball->position.x = Wwidth - ball->width;
        ball->kierunek_x = 0;
        ball->speed_Up(-15);
    }
    if(ball->position.x < 0)
    {
        ball->position.x = 0;
        ball->kierunek_x = 1;
        ball->speed_Up(-15);
    }

    if(ball->position.y+ball->height >= Wheight - player1->height)    //zderzenie z graczem 1
    {
        if(ball->position.x <= player1->position.x+player1->width && ball->position.x+ball->width >= player1->position.x)
        {
            ball->kierunek_y = 1;
            ball->position.y = player1->position.y-ball->height;
            //bonusy do predkosci przy zderzeniach
            if(ball->position.x+ball->width < (player1->position.x + (player1->width/3)))
                if(ball->kierunek_x == 0)
                    ball->odbicie(60);
                else
                    ball->odbicie(-60);
            else
            if(ball->position.x > (player1->position.x+player1->width-(player1->width/3)))
                if(ball->kierunek_x == 0)
                    ball->odbicie(-60);
                else
                    ball->odbicie(60);
            else
                ball->speed_Up(30);
            //a co jak sie poruszam
            if(ball->kierunek_x == 0 && player1->czylewo == true) ball->odbicie(120);
            if(ball->kierunek_x == 0 && player1->czyprawo == true) ball->odbicie(-360);
            if(ball->kierunek_x == 1 && player1->czylewo == true) ball->odbicie(-360);
            if(ball->kierunek_x == 1 && player1->czyprawo == true) ball->odbicie(120);
        }
    }
    if(ball->position.y <= player2->height)    //zderzenie z graczem 2
    {
        if(ball->position.x+ball->width >= player2->position.x-player2->width && ball->position.x <= player2->position.x)
        {
            ball->kierunek_y = 0;
            ball->position.y = player2->height;
            //bonusy do predkosci przy zderzeniach
            if(ball->position.x > (player2->position.x - (player2->width/3)))
                if(ball->kierunek_x == 0)
                    ball->odbicie(-90);
                else
                    ball->odbicie(90);
            else
            if(ball->position.x+ball->width < (player2->position.x-player2->width+(player2->width/3)))
                if(ball->kierunek_x == 0)
                    ball->odbicie(90);
                else
                    ball->odbicie(-90);
            else
                ball->speed_Up(30);

            //a co jak sie poruszam
            if(ball->kierunek_x == 0 && player2->czylewo == true) ball->odbicie(120);
            if(ball->kierunek_x == 0 && player2->czyprawo == true)ball->odbicie(-360);
            if(ball->kierunek_x == 1 && player2->czylewo == true) ball->odbicie(-360);
            if(ball->kierunek_x == 1 && player2->czyprawo == true) ball->odbicie(120);
        }
    }
}
