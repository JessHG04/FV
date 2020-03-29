#include "AnimationDarkrai.h"

AnimationDarkrai::AnimationDarkrai() {
    
}

AnimationDarkrai::AnimationDarkrai(sf::Texture* texture, sf::Vector2u matrizSprites, float tiempoCambio) {
    this->matrizSprites = matrizSprites;
    this->tiempoCambio = tiempoCambio;

    tiempoTotal = 0.0f;
    actualSprite.x = 0;

    coordenadasRect.width  = texture->getSize().x / float(matrizSprites.x);
    coordenadasRect.height = texture->getSize().y / float(matrizSprites.y);
}


AnimationDarkrai::~AnimationDarkrai() {

}


void AnimationDarkrai::Update(int fila, float deltaTime) {
    
    actualSprite.y = fila;
    tiempoTotal += deltaTime;

    // Cambia a la siguiente animación...
    if (tiempoTotal >= tiempoCambio) {
        tiempoTotal -= tiempoCambio;
        actualSprite.x++;

        // Reseteamos animación para que salga del sheet...
        if (actualSprite.x >= matrizSprites.x) {
            actualSprite.x = 0;
        }
    }

    coordenadasRect.left = actualSprite.x * coordenadasRect.width;
    coordenadasRect.top  = actualSprite.y * coordenadasRect.height;
}


sf::IntRect AnimationDarkrai::getCoordenadasRect() {
    return coordenadasRect;
}


sf::Vector2f AnimationDarkrai::getOrigin() {
    return sf::Vector2f(coordenadasRect.width/2, coordenadasRect.height);
}