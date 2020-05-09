#pragma once
#include <SFML/Graphics.hpp>

class SpriteBoss{

    public:
        //propiedades
        int cantidadXBoss;
        int cantidadYBoss;
        //parte de la pantalla que se usa
        sf::Vector2i frActualBoss;
        sf::Vector2f tamFrameBoss;
        //textura actualizacion
        sf::Texture *txActualBoss;
        sf::RectangleShape cajaColisionesBoss;

        //constrcutor   
        SpriteBoss();
        //sprite para el personaje
        sf::Sprite *spriteBoss;
        //textura para sprite
        sf::Texture *txBoss;
        //cambiar sprite
        void cambiarSpriteBoss(sf::Texture *textura, int x, int y, sf::Vector2i frm_act);
        //carga el frame correspondiente actual
        void seleccionarFrameBoss();
        //cambiar frame en fila
        void cambiarFrameXBoss(int frame);
        //cambiar frame en columna
        void cambiarFrameYBoss(int frame);
        //animacion
        void animarBoss();
        //animacion perder
        bool animarMuerteBoss();
};