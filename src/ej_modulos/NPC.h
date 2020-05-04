#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteNPC.h"
#include <iostream>
#include <string>
#include <vector>
#include "Jugador.h"


enum estadosNPC{
    paradoNPC = 1,
    andandoNPC  = 2,
    muertoNPC = 3
};

enum direccionesNPC{
    quietoNPC = 0, 
    arribaNPC = 1, 
    izquierdaNPC = 2,
    derechaNPC = 3, 
    abajoNPC = 4
};

class NPC:public SpriteNPC{

    private:
        //posicion
        sf::Vector2f posEne;
        //velocidad
        sf::Vector2f velEne;

    public:
        //constructor
        NPC();
        int tipo;
        sf::String archivoEne;
        bool movimientoEne = false;
        bool inmortalEne = false;
        bool dobleColision = false;
        int movimientoDesplazaEne = 0;
        float velDesplazamientoEne;
        int vida;
        direccionesNPC direccionEne;
        direccionesNPC dirColisionEne;
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