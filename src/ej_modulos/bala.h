#ifndef bala_h
#define bala_h

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class bala{
    public:
        Texture *tex;
        int xx = 0, yy = 0;
        bala(int, int);
        void movimientoBala();
        Sprite getSprite();
        Sprite *spriteb;
        void hacerTransparente();      
};

#endif