#ifndef bala_h
#define bala_h

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class bala{
    public:
        Texture *tex;
        bala();
        void movimientoBala();
        Sprite devolverSprite();
    private:
        Sprite *spriteb;        
};

#endif