#include "Mago.h"

Mago::Mago(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //Inicializo la vida
    vida = 3;
    archivo = "resources/Sprites/Eugyn/";
    //spriteJugador = new spritePersonaje();
    set_sprite(txt_player, cantidadX1, cantidadY1, frm_act);
    vel_desp = 10.0f;
   
}

Mago::~Mago() {
    delete txt_player;
    delete txt_herido;
    delete txt_dash_I;
    delete txt_dash_D;
    delete txt_player2;
    delete txt_herido2;
    delete txt_dash_I2;
    delete txt_dash_D2;
    delete txt_ataque_I;
    delete txt_ataque_D;
    delete txt_proyectil;
}