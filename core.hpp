#ifndef engine_h
#define engine_h

#include "obiekty.hpp"
#include <sstream>
//########################################### Klasy
class engine
{
public:
    int load();
private:
    std::string name = "IcyPong";
    sf::RenderWindow *window;
    sf::Texture pilka_img;
    sf::Texture deska_img;
    sf::Texture bonus_img;
    sf::Texture win_img;
    sf::Font basefont;
    sf::Font infofont;
    //#############################
    pilka *ball=NULL;
    deska *player1=NULL,*player2=NULL;
    bonus *bonus_pack = NULL;
    messageMenager *MM;
    //#############################
    int doilu = 5;
    long FPS = 1;
    float Framerate = 200;
    int Wwidth = 0,Wheight = 0;
    //#############################
    void CPU();
    void collisions();
    int los(int min_l = 0,int max_l = 1);
    //#############################
    void go(int fullscreen = 0,int width = 800,int height = 600);
    void playthegame(int players=1);
    void endofgame(std::string winer = "none");
};

//########################################### Wzorce
template <typename liczba>
std::string ToString(liczba l)
{
    std::ostringstream nap;
    nap << l;
    return nap.str();
}

#endif
