#ifndef messageMenager_h
#define messageMenager_h

#include <SFML/Graphics.hpp>

class message
{
    public:
        sf::String getText();
        message(sf::String what_mess,int what_id,long what_time);
        message *next = NULL;
    private:
        int id;
        sf::String text;
        long time;
};

class messageMenager
{
    public:
        messageMenager(int how_long,sf::Font *czcionka);
        void nowa(sf::String wiadomosc);
        void wyswietl(sf::RenderWindow *ekran);
    private:
        int time;
        int lastid=0;
        sf::Clock *zegar = NULL;
        sf::Font *font = NULL;
        message *first_mess = NULL;
};

#endif
