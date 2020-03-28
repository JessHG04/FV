#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "include/config.h"
#include "ej_modulos/Darkrai.h"

#define kVel 5

int main() {

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
  window.setFramerateLimit(60);

  sf::Texture tex;
  tex.loadFromFile("resources/sprites.png");

  sf::Sprite sprite(tex);
  sprite.setOrigin(75 / 2, 75);
  //Cojo el sprite que me interesa por defecto del sheet
  sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
  sprite.setPosition(50, 50);

  Darkrai* fantasma = new Darkrai(300, 200, 15.0, sprite);
  sf::Clock reloj;
  float deltaTime;

  //Bucle del juego
  while (window.isOpen()) {

    deltaTime = reloj.restart().asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {

        //Si se recibe el evento de cerrar la ventana la cierro
        case sf::Event::Closed:
          window.close();
          break;
        //Se pulsó una tecla, imprimo su codigo
        case sf::Event::KeyPressed:

          //Verifico si se pulsa alguna tecla de movimiento
          switch (event.key.code) {

          //Mapeo del cursor
          case sf::Keyboard::Right:
            sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
            //Escala por defecto
            sprite.setScale(1, 1);
            sprite.move(kVel, 0);
            break;

          case sf::Keyboard::Left:
            sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
            //Reflejo vertical
            sprite.setScale(-1, 1);
            sprite.move(-kVel, 0);
            break;

          case sf::Keyboard::Up:
            sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
            sprite.move(0, -kVel);
            break;

          case sf::Keyboard::Down:
            sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
            sprite.move(0, kVel);
            break;
          
          case sf::Keyboard::A:
            fantasma->recibeGolpe();
            break;

          //Tecla ESC para salir
          case sf::Keyboard::Escape:
            window.close();
            break;

          //Cualquier tecla desconocida se imprime por pantalla su código
          default:
            std::cout << event.key.code << std::endl;
            break;
          }
      }
    }
    
    fantasma->Update(deltaTime);

    window.clear(sf::Color(150, 150, 150));
    fantasma->Draw(window);
    window.draw(sprite);
    window.display();
  }

  delete fantasma;

  return 0;
}