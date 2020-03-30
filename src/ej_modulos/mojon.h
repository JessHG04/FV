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
        int numVidas, avansa, posx, posxx;
        mojon(int, int);
        ~mojon();
        void Draw(RenderWindow &);
        void Update(mojon*, cuadradoD*, cuadradoI*);
        void cambiarSprite(int);
        void cambiarSpriteDos(int);
        void perderVida();  
        Sprite getSprite();
        bool getMuerte();
        int getNumVidas();
    private:
        Sprite *sprite;
};

#endif