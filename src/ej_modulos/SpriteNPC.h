#pragma once
#include <SFML/Graphics.hpp>

class SpriteNPC{

    public:
        //propiedades
        int cantidadXNPC;
        int cantidadYNPC;
        //parte de la pantalla que se usa
        sf::Vector2i frActualNPC;
        sf::Vector2f tamFrameNPC;
        //textura actualizacion
        sf::Texture *txActualNPC;
        sf::RectangleShape cajaColisionesNPC;

        //constrcutor   
        SpriteNPC();
        //sprite para el personaje
        sf::Sprite *spriteNPC;
        //textura para sprite
        sf::Texture *txNPC;
        //cambiar sprite
        void cambiarSpriteNPC(sf::Texture *textura, int x, int y, sf::Vector2i frm_act);
        //carga el frame correspondiente actual
        void seleccionarFrameNPC();
        //cambiar frame en fila
        void cambiarFrameXNPC(int frame);
        //cambiar frame en columna
        void cambiarFrameYNPC(int frame);
        //animacion
        void animarNPC();
        //animacion perder
        bool animarMuerteNPC();
};