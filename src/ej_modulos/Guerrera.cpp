#include "Guerrera.h"

Guerrera::Guerrera(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //Inicializo la vida
    vida = 5;
    archivo = "resources/Sprites/Merche/";
    //spriteJugador = new spritePersonaje();
    set_sprite(txt_player2,cantidadX1, cantidadY1, frm_act);
    vel_desp = 7.3f;
}

Guerrera::~Guerrera() {
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