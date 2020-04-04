#pragma once
#include <SFML/Graphics.hpp>

class AnimationDarkrai {

    private:
    
        sf::Vector2u matrizSprites;   // filas y columnas de la imagen
        sf::Vector2u actualSprite;    // posicion del sprite actual en el sheet
        float tiempoTotal;            // tiempo transcurrido de la animacion
        float tiempoCambio;           // tiempo que se visualiza el sprite
        sf::IntRect coordenadasRect;  // coordenadas del sprite actual


    public:
        AnimationDarkrai();
        AnimationDarkrai(sf::Texture* texture, sf::Vector2u matrizSprites, float tiempoCambio);
        ~AnimationDarkrai();
        void Update(int fila, float deltaTime);
        sf::IntRect getCoordenadasRect();
        sf::Vector2f getOrigin();
};