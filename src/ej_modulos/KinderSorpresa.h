#pragma once

#include <SFML/Graphics.hpp>
#include "Enemigo.h"
#include "AnimationKinder.h"
#include "Proyectil.h"
#include "spritePersonaje.h"

class KinderSorpresa : public Enemigo {

    private:

        float speed;
        bool miraIzquierda = true;
        int ejecuta = 2;  // Animacion a ejecutar: 1->Movimiento, 2->Estatico
        int contando = 0;
        sf::Texture textura;
        sf::Sprite *body;
        sf::Sprite *personaje1;
        sf::Sprite *personaje2;
        sf::Clock relojAtaque;
        sf::Clock impactado;
        AnimationKinder *animacion;
        bool esGolpeado = false;
        int rangoMovimiento[2]; // Posicion en eje x por la que podra moverse el personaje
        bool estaAtacando = false;
        bool restartear = false, golpeado = false;
        sf::RectangleShape boundingSet[12];  // Cajas colisionables
        sf::RectangleShape *boundingBox;
        float ajustes[12];
        bool grande = false;


    public:

        KinderSorpresa(int ,int ,int ,float , sf::Sprite& ,sf::Sprite& ,int );
        ~KinderSorpresa();
        void Update(float );
        bool colisionProyectil(Proyectil *);
        void impactoProyectil();
        bool morir();
        void Draw(RenderWindow &);
        void recibeGolpe();
        bool colisionProtagonista(spritePersonaje *);
        void hacerTransparente();
        void hacerGrande();
        bool estaEnRango(sf::Sprite *);
        sf::RectangleShape getBoundingBox();
};