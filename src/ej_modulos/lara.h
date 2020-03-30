#ifndef lara_h
#define lara_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include "lara.h"
#include "Enemigo.h"
#include "cuadradoD.h"
#include "bala.h"

using namespace std;
using namespace sf;

class lara : public Enemigo{
    public:
        int direccion;
        Texture *tex;
        Clock reloja, relojb;
        int numVidas, avanza;
        bool fin, yasta = false;
        lara();
        void cambiarSprite(int);
        void restartSprite();
        Sprite devolverSprite();
        void Draw(RenderWindow &);
        void Update(RenderWindow &, lara*, cuadradoD*, bala*);
    private:
        Sprite *sprite;        
};

#endif