#include "Jugador.h"

Jugador::Jugador(){
}

void Jugador::update(){ //Actuaiza fisicas del jugador
    //if(movimiento){
        set_translacion(velocidad);
        cajaColisiones.setPosition(get_posicion().x - tamFrame.x/2, get_posicion().y - tamFrame.y/2);
    //}
}