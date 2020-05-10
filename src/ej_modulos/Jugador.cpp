#include "Jugador.h"

Jugador::Jugador(){
    termina_dash = new sf::Clock();
    recarga_dash = new sf::Clock();
    crono_recarga_dash = new sf::Time();
    crono_termina_dash = new sf::Time();
    sf::RectangleShape box2(sf::Vector2f(tamFrame.x + 30, 3));
    cajaColisiones2 = box2;
    cajaColisiones2.setFillColor(sf::Color::White);
}

void Jugador::update(float deltaTime){ //Actuaiza fisicas del jugador
    //if(movimiento){
  
    if(movimiento || inmortal){
        animar();
        /*
        if(atacando && frame_actual.x >= 1)
            atacando = false;
        recarga_proyectil->restart();
            */
    }
    set_translacion(sf::Vector2f(velocidad.x * deltaTime, velocidad.y * deltaTime));
    cajaColisiones3.setPosition(get_posicion().x - tamFrame.x/4, get_posicion().y - tamFrame.y/2 + tamFrame.y/10);
    cajaColisiones2.setPosition(get_posicion().x - 15 , get_posicion().y + tamFrame.y/2  + 2 - 8);

    //}
}

void Jugador::draw(sf::RenderWindow& window) {
 
    window.draw(*spr_player);

}