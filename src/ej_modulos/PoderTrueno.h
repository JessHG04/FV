#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteTrueno.h"
#include <iostream>
#include <string>
#include <vector>
#include "Jugador.h"


enum estadosTrueno{
    paradoT = 1,
    andandoT  = 2,
    muertoT = 3
};

enum direccionesTrueno{
    quietoT = 0, 
    arribaT = 1, 
    izquierdaT = 2,
    derechaT = 3, 
    abajoT = 4
};

class PoderTrueno:public SpriteTrueno{

    private:
        //posicion
        sf::Vector2f posEne;
        //velocidad
        sf::Vector2f velEne;

    public:
        //constructor
        PoderTrueno();
        int tipo;
        sf::String archivoEne;
        bool movimientoEne = false;
        bool inmortalEne = false;
        bool dobleColision = false;
        int movimientoDesplazaEne = 0;
        float velDesplazamientoEne;
        int vida;
        direccionesTrueno direccionEne;
        direccionesTrueno dirColisionEne;
        sf::Vector2f posInicialEne; 
        

        sf::Sprite getSpriteEne(){
            return *spriteNPC;
        }
        sf::Vector2f getPosicionEne(){
            return posEne;
        }

        int getPosicionXEne(){
            return posEne.x;
        }

        int getPosicionYEne(){
            return posEne.y;
        }

        void setPosEne(sf::Vector2f posic){
            posEne = posic;
            spriteNPC->setPosition(posEne);
        }

        void setTraEne(sf::Vector2f trans){
            posEne += trans;
            spriteNPC->setPosition(posEne);
        }
        void setVelEne(sf::Vector2f velocidad){
            velEne = velocidad;
        }

        void updateEne();//actualizar fisicas del jugador
        
        void cambiarPosicionEne(sf::Vector2f posicionNueva){
            posEne = posicionNueva;
            spriteNPC->setPosition(posEne);
        }
};