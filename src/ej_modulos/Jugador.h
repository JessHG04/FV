#pragma once
#include <SFML/Graphics.hpp>
#include "spritePersonaje.h"
#include <iostream>
#include <string>

enum estados{parado,andando,muerto};
enum direcciones{izq = 2,der = 3};

class Jugador : public spritePersonaje{
    public:
        //Constructor
        Jugador();
        //Destructor
        //~Jugador();

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
        sf::String archivo;
        bool movimiento = false;
        float vel_desp; // velocidad desplazamiento
        //-------------------------------------------SALTO---------------------------------------
        float vel_salto = -20.0f;
        bool saltando = false;
        //Variable para guardar al posiocn actual
        sf::Vector2f posInicial; 
        int vida;
        direcciones direccion;

    private:
        //spritePersonaje * spriteJugador;
        //Posicion del jugador
        sf::Vector2f posicion;
        sf::Vector2f velocidad; // velocidad actual
        
};