#include "Portal.h"

Portal::Portal(int x, int y){
    if(!text.loadFromFile("resources/Sprites/Portal.png")){ 
        std::cout << "Error cargando la textura del portal" << std::endl;
    }
    
    sprite = new sf::Sprite(text);
    sprite->setScale(0.25, 0.25);
    sprite->setOrigin(text.getSize().x/2, text.getSize().y/2);
    sprite->setPosition(x, y);
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