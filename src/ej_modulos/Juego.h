#pragma once
#include <SFML/Graphics.hpp>
#include "Mago.h"
#include "Guerrera.h"
#include "Proyectil.h"
#include "Map.h"
#include "Enemigo.h"
#include "bala.h"
#include "lara.h"

class Juego{
    public:
        Juego(sf::Vector2u tam_pantalla);
        void iniciar(); //Inicia variables y diferentes aspectos
        void dibujar(); //dibujar elementos
        void logica(); // procesa logicas del juego
        void procesar_eventos(); // elementos de entrada, teclado...
        void cortarEventoDash(int distancia);
        bool colisionPersMapa(direcciones direccion); //1 -> Arriba 2-> Izquierda 3-> Drcha 4->Abajo

    private:
        bool gameover = false;
        //Creamos al jugador
        Jugador *j1;
        //Creamos el proyectil de eugyn
        Proyectil *p1;
        //Creamos el mapa
        Map *mapa;
        //El evento que se recibe
        sf::Event *evento;
        // La ventana de nuestro juego
         sf::RenderWindow *ventana;
         //Creamos el reloj
         sf::Clock *reloj1;
         sf::Time *crono1;
         int fps;
         bool esGuerrera = false;
};