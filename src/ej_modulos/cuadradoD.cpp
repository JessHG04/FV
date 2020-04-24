#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define kVel 5

#include "cuadradoD.h"

cuadradoD::cuadradoD(){
        tex2 = new Texture();
        if (!tex2->loadFromFile("resources/yellow.png")) {
            std::cerr << "Error cargando la imagen yellow.png";
            exit(0);
        } 
        sprite2 = new Sprite(*tex2);
        //Le pongo el centroide donde corresponde
        sprite2->setOrigin(20, 20);
        //Cojo el sprite que me interesa por defecto del sheet
        sprite2->setTextureRect(sf::IntRect(0, 0, 40, 40));
        
        // Lo dispongo en el centro de la pantalla
        sprite2->setPosition(600, 80);
}

    Sprite cuadradoD::devolverSprite2(){
        return *sprite2;
    }