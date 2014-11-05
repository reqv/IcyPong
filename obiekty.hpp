#ifndef obiekty_h
#define obiekty_h

#include "message.hpp"

class obiekt
{
    public:
        int width;
        int height;
        float speed;
        sf::Sprite looks;
        sf::Vector2f position;
        int bonusID = 0;
        void speed_Up(float up = 1);
    protected:
        float normal_speed = 0;
};

class deska : public obiekt
{
    public:
        deska(float szerokosc,float wysokosc,float szybkosc,sf::String nazwa);
        bool czyactivate=false,czylewo=false,czyprawo=false;
        sf::String name;
};

class pilka : public obiekt
{
    public:
        pilka(float szerokosc,float wysokosc,float szybkosc);
        int kierunek_x,kierunek_y;
        void odbicie(float ile = 0);
        float kat_odbicia;
        void speed_Up(float up = 30);
        float speed;
    private:
        const float max_speed = 1000;
};

class bonus : public obiekt
{
    public:
        bonus(sf::Texture *obrazek,int b,int x,int y);
        ~bonus();
};

#endif // obiekty_h
