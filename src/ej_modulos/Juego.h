#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "Interfaz.h"
#include "NPC.h"
#include "SpriteNPC.h"
#include "PersonajeNPC.h"
#include "Trueno.h"
#include "Boss.h"
#include "PersonajeBoss.h"
#include "SpriteBoss.h"
#include "SpriteTrueno.h"
#include "PoderTrueno.h"
#include "ProyectilBoss.h"

#define tiempoUpdate 1000/15

class Juego{
    public:
        static Juego* getInstancia(sf::Vector2u tam_pantalla,  sf::RenderWindow *ventana, int idPersonaje);

    protected:
        Juego(sf::Vector2u tam_pantalla,  sf::RenderWindow *ventana, int idPersonaje);
        ~Juego(){

        };
        void iniciar(); //Inicia variables y diferentes aspectos
        void dibujar(); //dibujar elementos
        void procesar_eventos(); // elementos de entrada, teclado...
        void cortarEventoDash(int distancia);
        void impacto();
        void gestionGravedad();
        void crearEnemigos();
        void crearPortal(); //Crear el portal, reseteo de personaje y fondo
        void colisionPersPortal();
        bool colisionPersMapa(direcciones direccion); //1 -> Arriba 2-> Izquierda 3-> Drcha 4->Abajo
        bool colisionProyecMapa(direccionProyectil direccion);
        bool colisionPersTrampa(direcciones direccion);
        void colisionesProtagonista();
        void colisionProyectilEnemigos();
        void muerteNPCs();
        void detenerDash();
        void reiniciar();
        
    private:
        static Juego* juego;
        sf::Sprite *sp = NULL; //Segundo sprite al que persigue Kinder
        sf::Texture textFondo;
        sf::Sprite fondo;
        bool gameover = false;
        std::vector <Enemigo *> enemigos;
        //POSICIONES: D1 - D2 - D3 - M1 - M2 - M3 - K1 - K2 - K3 - L1 - L2 - L3
     
        int totalEnemigos;
        //Creamos al jugador
        Jugador *j1;
        //Creamos el proyectil de eugyn
        Proyectil *p1 = NULL;
        //Creamos el mapa
        Map *mapa = NULL;
        //Creamos a Darkrai
        Darkrai *darkrai1 = NULL;
        Darkrai *darkrai2 = NULL;
        Darkrai *darkrai3 = NULL;
        //Creamos al mojon
        mojon *mojoncito1 = NULL;
        mojon *mojoncito2 = NULL;
        mojon *mojoncito3 = NULL;
        //Creamos a kinder
        KinderSorpresa *kindercito1 = NULL;
        KinderSorpresa *kindercito2 = NULL;
        KinderSorpresa *kindercito3 = NULL;
        //Creamos a Lara 
        lara *larita1 = NULL;
        lara *larita2 = NULL;
        lara *larita3 = NULL;
        //NPC
        NPC *npc = NULL;
        sf::Texture conver1;
        sf::Texture conver2;
        sf::Texture conver3;
        sf::Texture conver4;
        std::vector<sf::Sprite> conversacionInicial;
        int variableAuxiliar = 0;
        //BOSS
        Boss *bossFinal = NULL;
        void bossLanza();
        void bossTrueno();
        PoderTrueno *trueno = NULL;
        PoderTrueno *trueno2 = NULL;
        sf::Clock *relojBoss;
        sf::Time *cronoBoss;
        sf::Clock *relojTrueno;
        sf::Time *cronoTrueno;
        ProyectilBoss *pBoss = NULL;
        std::vector<sf::IntRect> posiciones;
        //Creamos el portal
        Portal *portal = NULL;
        //Creamos la vista
        sf::View vista;
        //El evento que se recibe
        sf::Event *evento = NULL;
        // La ventana de nuestro juego
        sf::RenderWindow *ventana = NULL;
        //Creamos el reloj
        float deltaTime, interpolacion;
        sf::Clock clock;
        sf::Clock *reloj1 = NULL;
        sf::Time *crono1 = NULL;
        sf::Clock *relojInmortal = NULL;
        sf::Time *cronoInmortal = NULL;
        sf::Clock *relojEnemigos = NULL;
        sf::Clock *relojDanyo = NULL;
        sf::Clock *relojMuerte = NULL;
        sf::Time *cronoMuerte = NULL;
        sf::Clock *relojBossMover = NULL;
        sf::Time *cronoBossMover = NULL;
        sf::Clock relojMerche;
        sf::Clock *muerteBoss = NULL;
        //Creamos el texto para el HUD
        Interfaz *interfaz;
        //Musica de fondo de cada nivel
        sf::Music musicaNivel1;
        sf::Music musicaNivel2;
        sf::Music musicaNivel3;
        sf::Music musicaBoss1;
        sf::Music musicaBoss2;
        sf::Music musicaBoss3;
        sf::Music musicaCreditos;

        sf::Font font;
        sf::Text musicaGuia;
        sf::Texture text;
        sf::Texture text2;
        sf::Sprite sprit;

        //Efectos de sonido
        sf::Music efectoMagia;
        sf::Music golpeHacha;
        sf::Music hasMuertoSonido;

        //Transicion muerte
        sf::Text hasMuerto;
        sf::Sprite spriteMuerte;
        sf::Texture texturaMuerte;
        sf::Sprite fondoNegro;
        int personajeSelec = 0;
        int fps; 
        int valor = 0;
        bool esGuerrera = false;
        bool gravedad = true;
        bool dios = false;
        bool danyo, danyao = false, restartearMuerteBoss = false;
        int nEnemigos = 0;
        int level = 1;
        int maxLevels = 7;
        bool cargar = false;
        bool muerteDarkrai1, muerteDarkrai2, muerteDarkrai3, muerteMojon1, muerteMojon2, muerteMojon3, muerteKinder1, muerteKinder2, muerteKinder3, muerteLara1, muerteLara2, muerteLara3, muerteBossFinal = false;
        bool colisionaProyMapa = true;
        bool musicaOff = false;
        bool musicaOn = true;
        bool muerteMojon = false, muerteDarkrai = false, muerteLara = false, muerteKinder = false;
        bool muerteTransicion = false;
         bool proyBoss = false;
        bool empiezaLaBatalla = false;
        bool muerteNPC = false;
        bool transformacionBoss = false;
        bool parar = false;
        bool vuelveIz = false, vuelveDe = false;
        sf::Texture conver0;   
        sf::Texture conver5;
        sf::Texture conver5Boss;
        sf::Texture converBoss;
        std::vector<sf::Sprite> conversacionBoss;
        int variableAuxiliarBoss = 0;
        sf::Texture txCaraBoss;
        sf::Sprite caraBoss;

        bool colisionProyectilBoss();
        bool colisionBossJugador();
        bool colisionProyectilBossMapa();
        void movimientoBoss();
        void animarMuerteBossFinal();

        //CREAMOS ITEM
        sf::Sprite itemVida;
        sf::Sprite itemVida2;
        sf::Texture itemTextura;

        sf::Music cogerItem;
        bool dibujarItem = true;
        int random = 0;
};