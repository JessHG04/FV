#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/KinderSorpresa.h"

#define kVel 5

int main() {

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

  //Cargo la imagen donde reside la textura del sprite
  sf::Texture tex;
  if (!tex.loadFromFile("resources/sprites.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  
  sf::Sprite sprite(tex);
  sf::Sprite sp(tex);
  
  sf::Clock clock;
  float deltaTime = 0.0;

  
  //Cojo el sprite que me interesa por defecto del sheet
  sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

  sprite.setPosition(200, 10);
sprite.setOrigin(75 / 2, 75);

sp.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

  sp.setPosition(500, 10);
sp.setOrigin(75 / 2, 75);

  KinderSorpresa *kinder = new KinderSorpresa(100, 600, 250, 20.0, sprite, sp, 5);

  //Bucle del juego
  while (window.isOpen()) {
    deltaTime = clock.restart().asSeconds();
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

        case sf::Keyboard::Up:
          //Escala por defecto
          sprite.move(0, -kVel);
          break;
        
        case sf::Keyboard::Down:
          //Escala por defecto
          sprite.move(0, kVel);
          break;

        case sf::Keyboard::Left:
          sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          sprite.setScale(-1, 1);
          sprite.move(-kVel, 0);
          break;

        case sf::Keyboard::D:
          sp.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          sp.setScale(1, 1);
          sp.move(kVel, 0);
          break;

        case sf::Keyboard::W:
          //Escala por defecto
          sp.move(0, -kVel);
          break;
        
        case sf::Keyboard::S:
          //Escala por defecto
          sp.move(0, kVel);
          break;

        case sf::Keyboard::A:
          sp.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          sp.setScale(-1, 1);
          sp.move(-kVel, 0);
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

    kinder->Update(deltaTime);

    window.clear(sf::Color(150, 150, 150));
    window.draw(sprite);
    window.draw(sp);
    kinder->Draw(window);
    window.display();
  }

  delete kinder;

  return 0;
}