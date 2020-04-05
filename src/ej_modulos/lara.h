#ifndef lara_h
#define lara_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include "lara.h"
#include "Enemigo.h"
#include "cuadradoD.h"
#include "bala.h"
#include "mojon.h"
#include "spritePersonaje.h"
#include "Jugador.h"

using namespace std;
using namespace sf;

class lara : public Enemigo{
    public:
        Texture *tex;
        Clock reloja, relojb, relojc, relojd;
        int numVidas, avanza = 0;
        float coolDownDisparo = 3;
        bool fin, yasta = false, entra = false, entrada = false, esGolpeado = false;
        lara(int, int);
        void cambiarSprite(int, spritePersonaje*);
        void restartSprite();
        Sprite getSprite();
        void Draw(RenderWindow &);
        void Update(RenderWindow &, spritePersonaje*, int, int);
        void recibeGolpe();
    private:
        Sprite *sprite;
        bala *balera = nullptr;        
};

#endif