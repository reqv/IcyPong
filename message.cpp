#include "message.hpp"

//############################################################################# MANAGER
messageMenager::messageMenager(int how_long,sf::Font *czcionka,int font_w) //inicjacja menagera
{
    font_wt = font_w;
    time = how_long;
    font = czcionka;
    zegar = new sf::Clock;
    //ustawienia stringa
    text = new sf::Text;
    text->setFont(*font);
    text->setCharacterSize(font_wt);
}

void messageMenager::nowa(sf::String wiadomosc,int type,int posx,int posy) //Utworzene nowej wiadomosci
{
    message* nowa = new message(wiadomosc,globalID,zegar->getElapsedTime().asSeconds()+time,type);
    nowa->pos.x = posx;
    nowa->pos.y = posy;
    nowa->next = kolejka;
    kolejka = nowa;
    globalID++;
}

void messageMenager::wyswietl(sf::RenderWindow *ekran)  //wyswietlenie wszystkich wiadomosci
{
    if(kolejka == NULL) //jak nic nie ma
    {
        zegar->restart();
        globalID=0;
        return;
    }
    //PIERWSZY (czy do usuniecia)
    if(zegar->getElapsedTime().asSeconds() > kolejka->getTime())
    {
        delete(kolejka);
        kolejka = NULL;
        return;
    }
    //INNE
    message* start=kolejka;
    while(kolejka != NULL)
    {
        if(kolejka->next != NULL && zegar->getElapsedTime().asSeconds() > kolejka->next->getTime())
        {
            delete(kolejka->next);
            kolejka->next = NULL;
        }
        //############### wyswietl napis
        text->setString(kolejka->getText());
        //ustalenie pozycji
        if(kolejka->pos.x == 0 && kolejka->pos.y == 0)
        {
            kolejka->pos.x = ekran->getSize().x/2;
            kolejka->pos.y = ekran->getSize().y/2;
        }
        text->setPosition(kolejka->pos.x - (kolejka->howManyChars/2*font_wt),kolejka->pos.y - (font_wt/2));
        if(text->getPosition().x < 0)text->setPosition(0,text->getPosition().y);
        if(text->getPosition().x > ekran->getSize().x)text->setPosition(text->getPosition().x - 10 - (text->getPosition().x - ekran->getSize().x),text->getPosition().y);
        //okresl typ wiadomosci
        switch(kolejka->getType())
        {
            case 100:
                text->setColor(sf::Color::Yellow);
                text->setStyle(sf::Text::Bold);
            break;
            case 3:
                if(!kolejka->stored)
                {
                    kolejka->pos.x -= 5;
                    kolejka->pos.y += 5;
                    kolejka->stored = true;
                }
                else
                {

                    kolejka->pos.x += 5;
                    kolejka->pos.y -= 5;
                    kolejka->stored = false;
                }
                text->setColor(sf::Color::Magenta);
                text->setStyle(sf::Text::Italic | sf::Text::Bold);
            break;
            case 1:
                text->setColor(sf::Color::Blue);
                text->setStyle(sf::Text::Bold);
            break;
            case 0:
            default:
                if(!kolejka->stored)
                {
                    kolejka->pos.y-=100;
                    kolejka->stored = true;
                }else
                    kolejka->pos.y+=0.5;
                text->setColor(sf::Color::Red);
                text->setStyle(sf::Text::Bold);
        }
        ekran->draw(*text);
        kolejka = kolejka->next;
    }
    kolejka = start;
}

void messageMenager::clean()
{
    message* tmp=NULL;
    if(kolejka == NULL)return;
    while(kolejka->next != NULL)
    {
        tmp=kolejka->next;
        delete(kolejka);
        kolejka = tmp;
    }
    delete(kolejka);
    delete(text);
    font = NULL;
}
//############################################################################# MESSAGES
message::message(sf::String what_mess,int what_id,long what_time,int T)   //Format wiadomosci
{
    text = what_mess;
    time = what_time;
    type = T;
    howManyChars = what_mess.getSize();
    id=what_id;
}

sf::String message::getText()   //wiadomosc zwraca swoj tekst
{
    if(text.getSize() != 0)
        return text;
    else
        return "(error)";
}

float message::getTime()   //wiadomosc zwraca czas zakonczenia
{
    return time;
}

int message::getID()   //wiadomosc zwraca ID
{
    return id;
}

int message::getType()   //wiadomosc zwraca swoj typ
{
    return type;
}
