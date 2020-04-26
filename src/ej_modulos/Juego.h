#pragma once
#include <SFML/Graphics.hpp>
#include "Mago.h"
#include "Guerrera.h"
#include "Proyectil.h"
#include "Map.h"
#include "Enemigo.h"
#include "bala.h"
#include "lara.h"
#include "Darkrai.h"
#include "mojon.h"
#include "KinderSorpresa.h"

#define kUpdateTime 1000/15

class Juego{

    public:
        static Juego* getInstancia(sf::Vector2u );

    protected:
        Juego(sf::Vector2u tam_pantalla);
        ~Juego();
        void iniciar(); //Inicia variables y diferentes aspectos
        void dibujar(); //dibujar elementos
        void logica(); // procesa logicas del juego
        void procesar_eventos(); // elementos de entrada, teclado...
        void cortarEventoDash(int distancia);
        void gestionGravedad();
        bool colisionPersMapa(direcciones direccion); //1 -> Arriba 2-> Izquierda 3-> Drcha 4->Abajo
        bool colisionProyecMapa(direccionProyectil direccion);
        bool colisionPersTrampa(direcciones direccion);
        
    private:
        static Juego* juego;
        bool gameover = false;
        //Creamos al jugador
        Jugador *j1;
        //Creamos el proyectil de eugyn
        Proyectil *p1;
        //Creamos el mapa
        Map *mapa;
        //creamos enemigo
        Darkrai *darkrai;
        //Creamos a Lara
        lara *larita;
        cuadradoD *cuadra;
        //Creamos al mojon
        mojon *mojoncito;
        cuadradoI *cuadra2;
        //Creamos a kinder
        KinderSorpresa *kindercito;
        //Creamos la vista
        sf::View vista;
        //El evento que se recibe
        sf::Event *evento;
        // La ventana de nuestro juego
        sf::RenderWindow *ventana;
        float deltaTime; // IMPRESCINDIBLE
        //Creamos el reloj
        sf::Clock *reloj1;
        sf::Clock *reloj2;
        sf::Clock *relojInmortal;
        sf::Time *cronoInmortal;
        int fps;
        bool esGuerrera = false;
        bool gravedad = true;
};