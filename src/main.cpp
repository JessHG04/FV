#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Menu.h"
#include "ej_modulos/Juego.h"
#include "ej_modulos/Jugador.h"

int main() {

 Juego *juego = Juego::getInstancia(sf::Vector2u(960,640));

 
 return 0;
}
