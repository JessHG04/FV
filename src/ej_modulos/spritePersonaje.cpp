#include "spritePersonaje.h"

spritePersonaje::spritePersonaje(){
    
}

void spritePersonaje::set_sprite(sf::String file, int sprite, int cantidadX1, int cantidadY1, sf::Vector2i frm_act){
    //Variables
    cantidadX = cantidadX1; //Cantidad de grids en x
    cantidadY = cantidadY1; //Cantidad de grids en y
    sprite_actual = sprite; //Sprite a cargar
    txt_player = new sf::Texture(); //Textura de imagen
    sf::String cargaArchivo = file + std::to_string(sprite) + ".png"; //Archivo a cargar

    //Cargo la textura
    txt_player->loadFromFile(cargaArchivo); //Cargo el recurso desde la ruta
    spr_player = new sf::Sprite(*txt_player); //Nuevo sprite apartir de textura
    tamFrame = sf::Vector2f(txt_player->getSize().x / cantidadX, txt_player->getSize().y / cantidadY); //Dimension de cada frame haciendo la operacion
    frame_actual = frm_act; // cogemos el frame que queremos utilizar
    seleccionar_frame();
}

void spritePersonaje::seleccionar_frame(){
    sf::IntRect rectangulo(frame_actual.x * tamFrame.x,frame_actual.y * tamFrame.y,tamFrame.x,tamFrame.y); //Construimos el rectangulo del tamaño del frame que queremos
    spr_player->setTextureRect(rectangulo); // le insertamos el recorte al sprite
    
}

void spritePersonaje::animar(){
    if(frame_actual.x != (cantidadX-1)){ // si no alcance el ultimo frame
            frame_actual.x += 1; //incremento un frame
           
        
        
       
    }else{
        frame_actual.x = 0;
    }
     seleccionar_frame(); //selecciono el rectangulo correspondiente al frame
}

void spritePersonaje::set_frameX(int frame){
        frame_actual.x = frame;
        seleccionar_frame();
}

void spritePersonaje::set_frameY(int frame){
        frame_actual.y = frame;
        seleccionar_frame();
}
