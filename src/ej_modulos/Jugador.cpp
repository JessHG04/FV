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

void Jugador::update(float deltaTime){ //Actuaiza fisicas del jugador
    //if(movimiento){
  
    if(movimiento || inmortal){
        animar();
    }
    set_translacion(sf::Vector2f(velocidad.x * deltaTime, velocidad.y * deltaTime));
    cajaColisiones.setPosition(get_posicion().x - tamFrame.x/2, get_posicion().y - tamFrame.y/2);
    cajaColisiones2.setPosition(get_posicion().x - 30 , get_posicion().y + tamFrame.y/2  + 2 );

    //}
}

void Jugador::draw(sf::RenderWindow& window) {
 
    window.draw(*spr_player);

}