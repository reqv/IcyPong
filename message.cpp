#include "message.hpp"

//############################################################################# MANAGER
messageMenager::messageMenager(int how_long,sf::Font *czcionka)
{
    time = how_long;
    font = czcionka;
    zegar = new sf::Clock;
}

void messageMenager::nowa(sf::String wiadomosc)
{
    message* tmp;
    tmp = first_mess;
    while(tmp != NULL)tmp = tmp->next;
    tmp = new message(wiadomosc,lastid,zegar->getElapsedTime().asSeconds()+time);
    lastid++;
}

void messageMenager::wyswietl(sf::RenderWindow *ekran)
{
    if(first_mess == NULL)
    {
        lastid = 0;
        return;
    }
    message* tmp = first_mess;
    while(tmp != NULL)
    {
        //TUTAJ RYSOWANIE
        //ekran->draw()
        tmp = tmp->next;
    }
}
//############################################################################# MESSAGES
message::message(sf::String what_mess,int what_id,long what_time)
{
    text = what_mess;
    time = what_time;
    id=what_id;
}

sf::String message::getText()
{
    if(text.getSize() == 0)
        return text;
    else
        return "(error)";
}
