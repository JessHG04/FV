#ifndef enemigo_h
#define enemigo_h

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Enemigo {
    public:
        Enemigo(int );
        virtual ~Enemigo();
        void perderVida();  
        bool getMuerte();
        int getNumVidas();

    protected:
        int vidas;
        bool muerto = false;
};

#endif