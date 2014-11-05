#include "obiekty.hpp"

void obiekt::speed_Up(float up)
{
    if(up == 0)speed = normal_speed;
    else
        speed += up;
}
//################################### Palety i pilki

pilka::pilka(float szerokosc,float wysokosc,float szybkosc)
{
    width = szerokosc;
    height = wysokosc;
    normal_speed = szybkosc;
    speed = normal_speed;
    kat_odbicia = 0.0;
}

void pilka::speed_Up(float up)
{
    if(up == 0)speed = normal_speed;
    else
        speed += up;
    if(speed > max_speed)speed = max_speed;
    if(speed < normal_speed)speed = normal_speed;
}

void pilka::odbicie(float ile)
{
    if(ile == 0)kat_odbicia = 0;
    else
        kat_odbicia += ile;
    if(kat_odbicia < 0)
    {
        if(kierunek_x == 0)
            kierunek_x = 1;
        else
            kierunek_x = 0;
        kat_odbicia = -kat_odbicia;
    }
}

deska::deska(float szerokosc,float wysokosc,float szybkosc,sf::String nazwa)
{
    name = nazwa;
    obiekt::width = szerokosc;
    obiekt::height = wysokosc;
    normal_speed = szybkosc;
    speed = normal_speed;
}
//################################### Bonus
bonus::bonus(sf::Texture *obrazek,int b = 0,int x = 0,int y = 0)
{
    position.x = x;
    position.y = y;
    looks.setTexture(*obrazek);
    looks.setPosition(position.x,position.y);
    width = 20;
    height = 20;
    bonusID = b;
    speed = 0;
}

bonus::~bonus()
{

}
