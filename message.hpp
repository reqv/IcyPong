#ifndef messageMenager_h
#define messageMenager_h

#include <SFML/Graphics.hpp>

class message
{
    public:
        sf::String getText();
        float getTime();
        int getID();
        message(sf::String what_mess,int what_id,long what_time);
        message *next = NULL;
    private:
        int id;
        sf::String text;
        float time;
};

class messageMenager
{
    public:
        messageMenager(int how_long,sf::Font *czcionka);
        void nowa(sf::String wiadomosc);
        void wyswietl(sf::RenderWindow *ekran);
        void clean();
    private:
        int time;
        int globalID=0;
        sf::Clock *zegar = NULL;
        sf::Font *font = NULL;
        message *kolejka = NULL;
};

#endif
