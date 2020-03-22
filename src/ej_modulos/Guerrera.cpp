#include "Guerrera.h"

Guerrera::Guerrera(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //Inicializo la vida
    vida = 10;
    archivo = "resources/Sprites/Merche/";
    //spriteJugador = new spritePersonaje();
    set_sprite(archivo, 1, cantidadX1, cantidadY1, frm_act);
    vel_desp = 7.3f;
}