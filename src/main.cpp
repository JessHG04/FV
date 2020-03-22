#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Menu.h"
#include "ej_modulos/Juego.h"
#include "ej_modulos/Jugador.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(600,600),"Seleccion personaje - Gremory Hole");
    Menu menu(window.getSize().x,window.getSize().y);
    while(window.isOpen()){
      sf::Event evento;
      while(window.pollEvent(evento)){
        switch (evento.type)
        {
        case sf::Event::KeyReleased:
          switch (evento.key.code)
          {
          case sf::Keyboard::Up:
            menu.moveUp();
            break;

          case sf::Keyboard::Down:
            menu.moveDown();  
            break;
          
          }
          case sf::Event::Closed:
            window.close();
            break;
        
       
        }
      }
      window.clear();
      menu.dibujar(window);
      window.display();
    }

 // Juego *juego = new Juego(sf::Vector2u(800,600));
 // return 0;
}
