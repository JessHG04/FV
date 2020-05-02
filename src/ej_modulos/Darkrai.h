#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Enemigo.h"
#include "AnimationDarkrai.h"


class Darkrai : public Enemigo {

    public:
        Darkrai(int ,int ,float ,sf::Sprite &);
        ~Darkrai();
        void Update(float deltaTime);
        void Draw(sf::RenderWindow &);
        sf::RectangleShape getBoundingBox();
        void recibeGolpe();
        sf::Sprite* getSprite();


    private:
        float speed;                    // velocidad de Darkrai
        unsigned int rowSheet = 0;               // sprites de la animacion a ejecutar del spritesheet
        bool miraIzquierda = true;     // Booleano para saber en que direccion mira
        sf::RectangleShape boundingSet[5];  // Cajas colisionables
        sf::RectangleShape *boundingBox;
        sf::Texture textura;
        sf::Sprite *body;
        sf::Sprite *personaje;
        AnimationDarkrai *animacion;
        bool esGolpeado = false;
        bool follow = false;
};