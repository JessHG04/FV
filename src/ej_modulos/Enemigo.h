#ifndef enemigo_h
#define enemigo_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Proyectil.h"
using namespace std;
using namespace sf;

class Enemigo {
    public:
        Enemigo();
        Enemigo(int );
        virtual ~Enemigo();
        void perderVida();  
        bool getMuerte();
        void setMuerte(bool);
        int getNumVidas();
        bool colisionProyectil(Proyectil *);
        virtual void recibeGolpe();
        virtual void Update(float );
        virtual void Draw(RenderWindow &);

    protected:
        int vidas;
        bool muerto = false;
};

#endif