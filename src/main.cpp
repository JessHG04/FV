#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#include "include/config.h"
#include "ej_modulos/mojon.h"
#include "ej_modulos/cuadradoD.h"
#include "ej_modulos/cuadradoI.h"
#include "ej_modulos/Enemigo.h"
#include "ej_modulos/lara.h"
#include "ej_modulos/bala.h"

#define kVel 5

int main() {
  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
  // MOJON

  mojon *npcMojonazo = new mojon(320, 500);
  cuadradoD *cuadradodd = new cuadradoD();
  cuadradoI *cuadradoii = new cuadradoI();
  // LARA CROFT
  lara *larita = new lara();
  cuadradoD *cuadri = new cuadradoD();

  while (window.isOpen()) {
    //Bucle de obtención de eventos
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
    window.clear();
    npcMojonazo->Update(npcMojonazo, cuadradodd, cuadradoii);
    larita->Update(window, larita, cuadri);
    npcMojonazo->Draw(window);
    larita->Draw(window);
    window.draw(cuadradodd->devolverSprite2());
    window.draw(cuadradoii->devolverSprite2());
    window.display();
  }

  return 0;
}