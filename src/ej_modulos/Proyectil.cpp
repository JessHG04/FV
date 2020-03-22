
#include "Proyectil.h"
#include "spritePersonaje.h"

Proyectil::Proyectil(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //spriteJugador = new spritePersonaje();
    file = "resources/Sprites/Proyectil/";
    set_sprite(file, 1, cantidadX1, cantidadY1, frm_act);
    vel_desp = 25.0f;
}
Proyectil::~Proyectil(){
    
}
void Proyectil::update(){ //Actuaiza fisicas del jugador
   
        set_translacion(velocidad);
    
}