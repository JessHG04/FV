#ifndef mojon_h
#define mojon_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemigo.h"
#include "cuadradoD.h"
#include "cuadradoI.h"

using namespace std;
using namespace sf;

class mojon : public Enemigo{
    public:
        int direccion;
        Texture *tex;
        Clock reloj;
        int numVidas, avansa, posx = 0, posxx = 0, x = 0, y = 0;
        mojon(int, int, int, int);
        ~mojon();
        void Draw(RenderWindow &);
        void Update(mojon*, cuadradoD*, cuadradoI*);
        void cambiarSprite(int);
        void cambiarSpriteDos(int);
        Sprite getSprite();
        void recibeGolpe();
    private:
        Sprite *sprite;
};

#endif