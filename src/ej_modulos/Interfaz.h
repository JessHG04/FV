#pragma once
#include <SFML/Graphics.hpp>
#include "spritePersonaje.h"

class Interfaz : public spritePersonaje{
    public:
        Interfaz(int clase);
        sf::Texture *txt_vida;
        sf::Texture *txt_cara;
        std::vector<sf::Sprite*>  spr_vida;
        sf::Sprite  *spr_cara;
        sf::String    nombre;
        sf::Text nombre2;
        sf::Font fuente;
};