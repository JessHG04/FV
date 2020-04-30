#include "Jugador.h"

Jugador::Jugador(){
    sf::RectangleShape box2(sf::Vector2f(tamFrame.x -30, 3));
    cajaColisiones2 = box2;
    cajaColisiones2.setFillColor(sf::Color::White);
}

void Jugador::update(){ //Actuaiza fisicas del jugador
    //if(movimiento){
        set_translacion(velocidad);
        cajaColisiones.setPosition(get_posicion().x - tamFrame.x/2, get_posicion().y - tamFrame.y/2);
        cajaColisiones2.setPosition(get_posicion().x , get_posicion().y + tamFrame.y/2 - 8);
    //}
}
