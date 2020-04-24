#pragma once

#include <SFML/Graphics.hpp>
#include "Enemigo.h"
#include "AnimationKinder.h"

class KinderSorpresa : public Enemigo {

    private:

        float speed;
        bool miraIzquierda = true;
        int ejecuta = 2;  // Animacion a ejecutar: 1->Movimiento, 2->Estatico
        sf::Texture textura;
        sf::Sprite *body;
        sf::Sprite *personaje1;
        sf::Sprite *personaje2;
        sf::Clock relojAtaque;
        AnimationKinder *animacion;
        bool esGolpeado = false;
        int rangoMovimiento[2]; // Posicion en eje x por la que podra moverse el personaje
        bool estaAtacando = false;
        sf::RectangleShape boundingSet[12];  // Cajas colisionables
        sf::RectangleShape *boundingBox;
        float ajustes[12];


    public:

        KinderSorpresa(int ,int ,int ,float , sf::Sprite& ,sf::Sprite& ,int );
        ~KinderSorpresa();
        void Update(float );
        void Draw(RenderWindow &);
        void recibeGolpe();
        bool estaEnRango(sf::Sprite *);
        sf::RectangleShape getBoundingBox();
};