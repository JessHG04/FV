#ifndef bala_h
#define bala_h

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class bala{
    public:
        Texture *tex;
        Sprite *spriteb;
        int xx = 0, yy = 0;
        bala();
        void movimientoBalaIz();
        void movimientoBalaDe();
        Sprite *getSprite();
        void hacerTransparente();
        void restartSprite();
        void Draw(RenderWindow&);    
};

#endif