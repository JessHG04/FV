#pragma once

#include <SFML/Graphics.hpp>
#include "Enemigo.h"
#include "AnimationDarkrai.h"
#include "Proyectil.h"
#include "spritePersonaje.h"
#include "Guerrera.h"

class Darkrai : public Enemigo {

    public:
        Darkrai(int ,int ,float ,sf::Sprite &);
        ~Darkrai();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        sf::RectangleShape getBoundingBox();
        void recibeGolpe(float );
        bool colisionProyectil(Proyectil *);
        void impactoProyectil();
        bool colisionProtagonista(Jugador *, bool);
        bool morir();
        void hacerTransparente();
        void restartSprite();
        sf::Sprite* getSprite();

    private:
        float speed;                    // velocidad de Darkrai
        unsigned int rowSheet = 0;               // sprites de la animacion a ejecutar del spritesheet
        bool miraIzquierda = true;     // Booleano para saber en que direccion mira
        int contando = 0;
        bool golpeado = false, restartear = false;
        Clock impactado;
        sf::RectangleShape boundingSet[5];  // Cajas colisionables
        sf::RectangleShape *boundingBox;
        sf::Texture textura;
        sf::Sprite *body;
        sf::Sprite *personaje;
        AnimationDarkrai *animacion;
        bool esGolpeado = false;
        bool follow = false;
};