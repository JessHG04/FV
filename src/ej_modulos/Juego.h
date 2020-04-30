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
#include "Portal.h"

class Juego{
    public:
        Juego(sf::Vector2u tam_pantalla,  sf::RenderWindow *ventana);
        void iniciar(); //Inicia variables y diferentes aspectos
        void dibujar(); //dibujar elementos
        void logica(); // procesa logicas del juego
        void procesar_eventos(); // elementos de entrada, teclado...
        void cortarEventoDash(int distancia);
        void gestionGravedad();
        void crearEnemigos();
        void crearPortal();
        void limpiarMapa();
        void colisionPersPortal();
        bool colisionPersMapa(direcciones direccion); //1 -> Arriba 2-> Izquierda 3-> Drcha 4->Abajo
        bool colisionProyecMapa(direccionProyectil direccion);
        bool colisionPersTrampa(direcciones direccion);
        
    private:
        bool gameover = false;
        std::vector <Enemigo *> enemigos;
        //Creamos al jugador
        Jugador *j1;
        //Creamos el proyectil de eugyn
        Proyectil *p1 = NULL;
        //Creamos el mapa
        Map *mapa = NULL;
        //creamos enemigo
        Darkrai *darkrai;
        //Creamos a Lara 
        lara *larita = NULL;
        //Creamos al mojon
        mojon *mojoncito = NULL;
        //Creamos el portal
        Portal *portal = NULL;
        //Creamos a kinder
        KinderSorpresa *kindercito = NULL;
        //Creamos la vista
        sf::View vista;
        //El evento que se recibe
        sf::Event *evento = NULL;
        // La ventana de nuestro juego
        sf::RenderWindow *ventana = NULL;
        //Creamos el reloj
        sf::Clock *reloj1 = NULL;
        sf::Time *crono1 = NULL;
        sf::Clock *relojInmortal = NULL;
        sf::Time *cronoInmortal = NULL;
        int fps;
        bool esGuerrera = false;
        bool gravedad = true;
        int level = 1;
        int maxLevels = 6;
        bool cargar = false;
};