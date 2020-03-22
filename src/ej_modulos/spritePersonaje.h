#pragma once
#include <SFML/Graphics.hpp>

class spritePersonaje{
    public: 
        spritePersonaje();
        
        //Creo el sprite del jugador
        sf::Sprite *spr_player;
        //Textura para el sprite
        sf::Texture *txt_player;
        void set_sprite(sf::String file, int sprite, int cantidadX1, int cantidadY1 , sf::Vector2i frm_act);
        void seleccionar_frame(); //carga el frame actual(por si se cambia)
        void set_frameX(int frame); // modifica el frame actual en fila
        void set_frameY(int frame); // modifica el frame actual en columna
        void animar(); //--------------------------------ANIMACION-----------------------------------------------

        // Sprite que va a usar
        int sprite_actual;
        int cantidadX;
        int cantidadY;
        sf::Vector2i frame_actual; // parte de la plantilla de sprites que se usa
        sf::Vector2f tamFrame;
        
};