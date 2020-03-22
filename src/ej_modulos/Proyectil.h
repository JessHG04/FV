#pragma once
#include <SFML/Graphics.hpp>
#include "spritePersonaje.h"

class Proyectil : public spritePersonaje{
    public:

         Proyectil(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act);
         ~Proyectil();

        
        // Obtener el sprite del jugador
        sf::Sprite get_sprite(){ 
            return *spr_player;
        }
        sf::Vector2f get_posicion(){ 
            return posicion;
        }
        void set_posicion(sf::Vector2f pos){
            posicion = pos;
            spr_player->setPosition(posicion);
        }

        void set_translacion(sf::Vector2f trans){
            posicion += trans;
            spr_player->setPosition(posicion);
        }
        void set_velocidad(sf::Vector2f vel){
            velocidad = vel;
        }

        void update();//actualizar fisicas del jugador
        
        int eliminar = 0;
        sf::Vector2f posicionInicial;
        float vel_desp; // velocidad desplazamiento
        sf::String file;

    private:
        sf::Vector2f posicion;
        sf::Vector2f velocidad; // velocidad actual
};
    
        

