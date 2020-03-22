#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/Map.h"

int main(){
    //Creacion de ventana
    sf::RenderWindow window(sf::VideoMode(960, 640), "Prueba mapa");

    //Objeto tipo Map
    Map *mapa = new Map();
    
    mapa->mapMatrix(); //Se guarda los datos del mapa
    mapa->load("resources/Tileset.png", sf::Vector2u(16,16), mapa->tilemap, mapa->widthMap, mapa->heightMap, mapa->numLayers);

    //std::cout << "Voy para el bucle del juego" << std::endl;

    //GameLoop
    while(window.isOpen()){
        //Ventana en color blanco
        window.clear(sf::Color::White);

        //Dibujo el mapa revisar
        //window.draw(map);

        //Bucle de obtencion de eventos
        sf::Event event;
        while (window.pollEvent(event)){
            switch ((event.type)){
            case sf::Event::Closed:
                window.close();
                break;

            //Verificacion de mis teclas
            case sf::Event::KeyPressed:
                switch (event.key.code){
                    //Tecla escape para salir
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        std::cout << event.key.code << std::endl;
                        break;
                }
            }
        }
        window.clear();
        window.draw(*mapa);
        window.display();
    }
    return 0;
}