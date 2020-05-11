#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteBoss.h"
#include <iostream>
#include <string>
#include <vector>
#include "Proyectil.h"
#include "spritePersonaje.h"


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
        bool restartear = false;

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
        int vida = 0;
        direccionesBoss direccionBoss;
        direccionesBoss dirColisionBoss;
        sf::Vector2f posInicialBoss; 
        sf::Clock impactado;
        bool golpeado = false;
        int contando = 0;
        bool muerto = false;
        bool colisionProyectil(Proyectil *p1);
        void impactoProyectil();
        void perderVida();
        bool getMuerte();
        void setMuerte(bool);
        void restartSprite();
        void hacerTransparente();
        bool morir();
        bool colisionProtagonista(spritePersonaje *);

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

        //CAMBIOOOOOOOO
        void colocarBoss();
        sf::Clock relojAnimacion;
};