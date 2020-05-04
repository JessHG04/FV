#include "Jugador.h"

Jugador::Jugador(){
    termina_dash = new sf::Clock();
    recarga_dash = new sf::Clock();
    crono_recarga_dash = new sf::Time();
    crono_termina_dash = new sf::Time();
    sf::RectangleShape box2(sf::Vector2f(tamFrame.x + 60, 5));
    cajaColisiones2 = box2;
    cajaColisiones2.setFillColor(sf::Color::White);
}

void Jugador::update(){ //Actuaiza fisicas del jugador
    //if(movimiento){
        set_translacion(velocidad);
        cajaColisiones.setPosition(get_posicion().x - tamFrame.x/2, get_posicion().y - tamFrame.y/2);
        cajaColisiones2.setPosition(get_posicion().x - 30 , get_posicion().y + tamFrame.y/2  + 2 );
    //}
}