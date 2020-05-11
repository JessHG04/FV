#pragma once
#include <SFML/Graphics.hpp>
#include "spritePersonaje.h"

enum direccionProyectilBoss{izquierdaProyectilBoss = 1, derechaProyectilBoss = 2}; 

class ProyectilBoss : public spritePersonaje{
    public:

         ProyectilBoss(int cantidadX1, int cantidadY1 , sf::Vector2i frm_act);
         ~ProyectilBoss();

        
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
        
        sf::Vector2f posicionInicial;
        float vel_desp; // velocidad desplazamiento
        sf::String file;
        direccionProyectilBoss dirColisionProyectilBoss;

    private:
        sf::Vector2f posicion;
        sf::Vector2f velocidad; // velocidad actual
};
    
        
