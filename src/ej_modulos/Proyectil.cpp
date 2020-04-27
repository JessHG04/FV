
#include "Proyectil.h"
#include "spritePersonaje.h"

Proyectil::Proyectil(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //spriteJugador = new spritePersonaje();
    file = "resources/Sprites/Proyectil/";
    set_sprite(txt_proyectil, cantidadX1, cantidadY1, frm_act);
    vel_desp = 25.0f;
}
Proyectil::~Proyectil(){
    
}
void Proyectil::update(){ //Actuaiza fisicas del jugador
        cajaColisiones.setPosition(get_posicion().x - tamFrame.x/2, get_posicion().y - tamFrame.y/2);
        set_translacion(velocidad);
    
}