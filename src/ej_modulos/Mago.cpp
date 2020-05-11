#include "Mago.h"

Mago::Mago(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //Inicializo la vida
    vida = 3;
    archivo = "resources/Sprites/Eugyn/";
    //spriteJugador = new spritePersonaje();
    set_sprite(txt_player, cantidadX1, cantidadY1, frm_act);
    vel_desp = 10.0f;
   
}

