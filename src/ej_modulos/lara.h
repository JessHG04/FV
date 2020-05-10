#ifndef lara_h
#define lara_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include "lara.h"
#include "Enemigo.h"
#include "cuadradoD.h"
#include "bala.h"
#include "mojon.h"
#include "Guerrera.h"
#include "Proyectil.h"
#include "Map.h"

using namespace std;
using namespace sf;

class lara : public Enemigo{
    public:
        Texture *tex;
        Clock reloja, relojd, impactado;
        bool lado = false, es = false, disparo = false, shoot = false, dispara = false;
        int numVidas, avanza = 0;
        int contando = 0;
        float coolDownDisparo = 1;
        bool fin, yasta = false, entra = false, entrada = false, esGolpeado = false, golpeado = false, restartear = false;
        lara(int, int);
        void cambiarSprite(int, spritePersonaje*);
        void restartSprite();
        Sprite getSprite();
        void Draw(RenderWindow &);
        bool Update(RenderWindow &, spritePersonaje*, int, int, Map *);
        bool colisionBalaMapa(bala *, Map *);
        bool colisionProyectil(Proyectil *);
        void colisionProtagonista(Jugador *,bool );
        bool morir();
        void impactoProyectil();
        void recibeGolpe();
        void hacerTransparente();
        bala getBala();
    private:
        Sprite *sprite;
        bala *balera = nullptr;        
};

#endif
