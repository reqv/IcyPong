#ifndef messageMenager_h
#define messageMenager_h

#include <SFML/Graphics.hpp>

class message
{
    public:
        sf::String getText();
        float getTime();
        int getID();
        int getType();
        void onScreen();
        message(sf::String what_mess,int what_id,long what_time,int T);
        message *next = NULL;
        sf::Vector2f pos;
        int howManyChars = 0;
        bool stored;
    private:
        int id;
        int type;
        sf::String text;
        float time;
};

class messageMenager
{
    public:
        messageMenager(int how_long,sf::Font *czcionka,int font_w = 22);
        void nowa(sf::String wiadomosc,int type=0,int posx=0,int posy=0);
        void wyswietl(sf::RenderWindow *ekran);
        void clean();
    private:
        int time;
        int font_wt;
        int globalID=0;
        sf::Clock *zegar = NULL;
        sf::Font *font = NULL;
        sf::Text *text = NULL;
        message *kolejka = NULL;
};

#endif
