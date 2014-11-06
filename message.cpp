#include "message.hpp"
#include <stdio.h>
#include <iostream>

#include "core.hpp"

//############################################################################# MANAGER
messageMenager::messageMenager(int how_long,sf::Font *czcionka) //inicjacja menagera
{
    time = how_long;
    font = czcionka;
    zegar = new sf::Clock;
    std::cout<<"Hello! Its MM !"<<std::endl;
}

void messageMenager::nowa(sf::String wiadomosc) //Utworzene nowej wiadomosci
{
    message* nowa = new message(wiadomosc,globalID,zegar->getElapsedTime().asSeconds()+time);
    nowa->next = kolejka;
    kolejka = nowa;
    globalID++;
}

void messageMenager::wyswietl(sf::RenderWindow *ekran)  //wyswietlenie wszystkich wiadomosci
{
    if(kolejka == NULL) //jak nic nie ma
    {
        std::cout<<"reset"<<std::endl;
        zegar->restart();
        globalID=0;
        return;
    }
    std::string lolo;
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
        lolo = kolejka->getText().toAnsiString();
        std::cout<<lolo<<std::endl;
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
}
//############################################################################# MESSAGES
message::message(sf::String what_mess,int what_id,long what_time)   //Format wiadomosci
{
    text = what_mess;
    time = what_time;
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
