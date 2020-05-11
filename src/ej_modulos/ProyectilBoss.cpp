
#include "ProyectilBoss.h"
#include "spritePersonaje.h"

ProyectilBoss::ProyectilBoss(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act){
    //spriteJugador = new spritePersonaje();
    file = "resources/Sprites/ProyectilBoss/";
    set_sprite(txt_proyectilBoss, cantidadX1, cantidadY1, frm_act);
    vel_desp = 25.0f;
}
ProyectilBoss::~ProyectilBoss(){
    
}
void ProyectilBoss::update(){ //Actuaiza fisicas del jugador
   
        set_translacion(velocidad);
    
}