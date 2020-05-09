#include "Interfaz.h"


Interfaz::Interfaz(int clase){

    txt_vida = new sf::Texture(); //Textura de imagen
    txt_cara = new sf::Texture(); //Textura de imagen

    txt_vida->loadFromFile("resources/Sprites/Vida/" + std::to_string(1) + ".png"); //Cargo el recurso desde la ruta
    
    int v = 0;
    if(clase == 1){
        nombre = "Mercedes";
        txt_cara->loadFromFile("resources/Sprites/Merche/" + std::to_string(100) + ".png"); //Cargo el recurso desde la ruta
        v = 5;
    }else{
        nombre = "Eugyn";
        txt_cara->loadFromFile("resources/Sprites/Eugyn/" + std::to_string(100) + ".png"); //Cargo el recurso desde la ruta
        v = 3;
    }
  
    for(int i = 0; i < v ; i++){
         sf::Sprite *spr_vida_aux = new sf::Sprite(*txt_vida); //Nuevo sprite apartir de textura#include <vector>
         spr_vida_aux->setScale(0.06,0.06);
         spr_vida_aux->setPosition(95 + i*30, 30);
         spr_vida.push_back(spr_vida_aux);
    }
    
    spr_cara = new sf::Sprite(*txt_cara); //Nuevo sprite apartir de textura
    spr_cara->setPosition(100,5);
    spr_cara->setScale(-1.5,1.5);
    spr_cara->setTexture(*txt_cara);

    nombre2.setString(nombre);
    fuente.loadFromFile("resources/dark.TTF");
    nombre2.setFont(fuente);
    nombre2.setColor(sf::Color::White);
	nombre2.setCharacterSize(20);
	nombre2.setPosition(sf::Vector2f(100,5));
    
}