#include "Portal.h"

Portal::Portal(int x, int y){
    if(!text.loadFromFile("resources/Sprites/Portal.png")){ 
        std::cout << "Error cargando la textura del portal" << std::endl;
    }
    
    sprite = new sf::Sprite(text);
    sprite->setScale(0.25, 0.25);
    sprite->setOrigin(text.getSize().x/2, text.getSize().y/2);
    sprite->setPosition(x, y);
    cajaColision = sf::RectangleShape(sf::Vector2f(text.getSize().x * 0.25, text.getSize().y * 0.25));
    cajaColision.setFillColor(sf::Color::Blue);
    /*
    std::cout << "Posicion X: " << sprite->getPosition().x << std::endl;
    std::cout << "Posicion X2: " << sprite->getPosition().x - 64 << std::endl;
    std::cout << "Posicion Y: " << sprite->getPosition().y << std::endl;
    std::cout << "Posicion Y2: " << sprite->getPosition().y - 64 << std::endl;
    */
    cajaColision.setPosition(sprite->getPosition().x - 64, sprite->getPosition().y - 64);
}

Portal::~Portal(){
    delete sprite;
}

sf::RectangleShape Portal::getCaja(){
    return cajaColision;
}

void Portal::Update(){
    //std::cout << "Delta time: " << deltaTime << std::endl;
    sprite->rotate(4);
}

void Portal::Draw(sf::RenderWindow &ventana){
    if(sprite != NULL){
        ventana.draw(*sprite);
    }
}