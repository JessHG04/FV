#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteBoss.h"
#include <iostream>
#include <string>
#include <vector>


enum estadosBoss{
    paradoBoss = 1,
    andandoBoss  = 2,
    muertoBoss = 3
};

enum direccionesBoss{
    quietoBoss = 0, 
    arribaBoss = 1, 
    izquierdaBoss = 2,
    derechaBoss = 3, 
    abajoBoss = 4
};

class Boss:public SpriteBoss{

    private:
        //posicion
        sf::Vector2f posBoss;
        //velocidad
        sf::Vector2f velBoss;

    public:
        //constructor
        Boss();
        int tipo;
        sf::String archivoBoss;
        bool movimientoBoss = false;
        bool inmortalBoss = false;
        bool dobleColision = false;
        int movimientoDesplazaBoss = 0;
        float velDesplazamientoBoss;
        int vida;
        direccionesBoss direccionBoss;
        direccionesBoss dirColisionBoss;
        sf::Vector2f posInicialBoss; 
        

        sf::Sprite getSpriteBoss(){
            return *spriteBoss;
        }
        sf::Vector2f getPosicionBoss(){
            return posBoss;
        }

        int getPosicionXBoss(){
            return posBoss.x;
        }

        int getPosicionYBoss(){
            return posBoss.y;
        }

        void setPosBoss(sf::Vector2f posic){
            posBoss = posic;
            spriteBoss->setPosition(posBoss);
        }

        void setTraBoss(sf::Vector2f trans){
            posBoss += trans;
            spriteBoss->setPosition(posBoss);
        }
        void setVelBoss(sf::Vector2f velocidad){
            velBoss = velocidad;
        }

        void updateBoss();//actualizar fisicas del jugador
        
        void cambiarPosicionBoss(sf::Vector2f posicionNueva){
            posBoss = posicionNueva;
            spriteBoss->setPosition(posBoss);
        }
};