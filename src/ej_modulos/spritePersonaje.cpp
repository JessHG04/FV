#include "spritePersonaje.h"

spritePersonaje::spritePersonaje(){
    txt_player = new sf::Texture(); //Textura de imagen
    txt_herido = new sf::Texture(); //Textura de imagen
    txt_dash_D = new sf::Texture(); //Textura de imagen
    txt_dash_I = new sf::Texture(); //Textura de imagen
    txt_player2 = new sf::Texture(); //Textura de imagen
    txt_herido2 = new sf::Texture(); //Textura de imagen
    txt_dash_D2 = new sf::Texture(); //Textura de imagen
    txt_dash_I2 = new sf::Texture(); //Textura de imagen
    txt_ataque_D = new sf::Texture(); //Textura de imagen
    txt_ataque_I = new sf::Texture(); //Textura de imagen
    txt_proyectil = new sf::Texture();

    //Cargo la textura
    txt_player->loadFromFile("resources/Sprites/Eugyn/" + std::to_string(1) + ".png"); //Cargo el recurso desde la ruta
    txt_herido->loadFromFile("resources/Sprites/Eugyn/" + std::to_string(9) + ".png"); //Cargo el recurso desde la ruta
    txt_dash_D->loadFromFile("resources/Sprites/Eugyn/" + std::to_string(4) + ".png"); //Cargo el recurso desde la ruta
    txt_dash_I->loadFromFile("resources/Sprites/Eugyn/" + std::to_string(2) + ".png"); //Cargo el recurso desde la ruta
    txt_player2->loadFromFile("resources/Sprites/Merche/" + std::to_string(1) + ".png"); //Cargo el recurso desde la ruta
    txt_herido2->loadFromFile("resources/Sprites/Merche/" + std::to_string(9) + ".png"); //Cargo el recurso desde la ruta
    txt_dash_D2->loadFromFile("resources/Sprites/Merche/" + std::to_string(4) + ".png"); //Cargo el recurso desde la ruta
    txt_dash_I2->loadFromFile("resources/Sprites/Merche/" + std::to_string(2) + ".png"); //Cargo el recurso desde la ruta
    txt_ataque_D->loadFromFile("resources/Sprites/Merche/"+ std::to_string(7) + ".png"); //Cargo el recurso desde la ruta
    txt_ataque_I->loadFromFile("resources/Sprites/Merche/"+ std::to_string(6) + ".png"); //Cargo el recurso desde la ruta
    txt_proyectil->loadFromFile("resources/Sprites/Proyectil/" + std::to_string(1) + ".png"); 
    /*delete spr_player;
    spr_player = 0;*/
    spr_player = new sf::Sprite(*txt_player); //Nuevo sprite apartir de textura
}

void spritePersonaje::set_sprite(sf::Texture *textura, int cantidadX1, int cantidadY1, sf::Vector2i frm_act){
    //Variables
    cantidadX = cantidadX1; //Cantidad de grids en x
    cantidadY = cantidadY1; //Cantidad de grids en y
   /*delete txt_player;
    txt_player = 0;*/
    textura_actual = textura;
    spr_player->setOrigin((textura_actual->getSize().x / cantidadX) / 2, (textura_actual->getSize().y / cantidadY) / 2);
    spr_player->setTexture(*textura);
    
    tamFrame = sf::Vector2f(textura_actual->getSize().x / cantidadX, textura_actual->getSize().y / cantidadY); //Dimension de cada frame haciendo la operacion    
    frame_actual = frm_act; // cogemos el frame que queremos utilizar
    //spr_player->setScale(0.5,0.5);
    seleccionar_frame(); 
    sf::RectangleShape box(sf::Vector2f(tamFrame.x-20, tamFrame.y-20));
    cajaColisiones = box;
    cajaColisiones.setFillColor(sf::Color::Blue);
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

sf::Sprite spritePersonaje::getSprite(){
    return *spr_player;
}