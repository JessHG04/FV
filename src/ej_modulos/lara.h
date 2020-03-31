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
        Texture *tex;
        Clock reloja, relojb;
        int numVidas, avanza = 0;
        float coolDownDisparo = 6;
        bool fin, yasta = false;
        lara();
        void cambiarSprite(int);
        void restartSprite();
        Sprite devolverSprite();
        void Draw(RenderWindow &);
        void Update(RenderWindow &, lara*, cuadradoD*);
    private:
        Sprite *sprite;
        bala *balera = nullptr;        
};

#endif