#include "SpriteTrueno.h"
using namespace std;
#include <iostream>

//constructor   
SpriteTrueno::SpriteTrueno(){
    //textura de imagen
    txNPC = new sf::Texture();
    //cargo la textura
    //ruta de acceso al sprite
    sf::String ruta = "resources/Sprites/Trueno/trueno2.png";
    //cargar textura
    txNPC->loadFromFile(ruta);
    //nuevo sprite a partir de la textura
    spriteNPC = new sf::Sprite(*txNPC);
}

//cambiar sprite
void SpriteTrueno::cambiarSpriteNPC(sf::Texture *textura, int n1, int n2, sf::Vector2i frm){
    //grids en x
    cantidadXNPC = n1;
    //grids en y
    cantidadYNPC = n2;
    txActualNPC = textura;

    spriteNPC->setOrigin((txActualNPC->getSize().x / cantidadXNPC) / 2, (txActualNPC->getSize().y / cantidadYNPC) / 2);
    //spriteJugador->setOrigin((txActual->getSize().x) / 2, (txActual->getSize().y / 2));
    spriteNPC->setTexture(*textura);
    tamFrameNPC = sf::Vector2f(txActualNPC->getSize().x / cantidadXNPC, txActualNPC->getSize().y / cantidadYNPC); //Dimension de cada frame haciendo la operacion    
    frActualNPC = frm; // cogemos el frame que queremos utilizar
    spriteNPC->setScale(0.6,0.6);
    seleccionarFrameNPC(); 
    sf::RectangleShape box(sf::Vector2f(tamFrameNPC.x, tamFrameNPC.y));
    cajaColisionesNPC = box;
    cajaColisionesNPC.setFillColor(sf::Color::Transparent);
}

//carga el frame correspondiente actual
void SpriteTrueno::seleccionarFrameNPC(){
    sf::IntRect rectangulo(frActualNPC.x * tamFrameNPC.x,frActualNPC.y * tamFrameNPC.y,tamFrameNPC.x,tamFrameNPC.y); //Construimos el rectangulo del tamaño del frame que queremos
    spriteNPC->setTextureRect(rectangulo); // le insertamos el recorte al sprite
}

//animacion
void SpriteTrueno::animarNPC(){
    //no es el ultimo frame
    if(frActualNPC.x != (cantidadXNPC-1)){
        frActualNPC.x += 1;
    }else{
        frActualNPC.x = 0;
    }
    seleccionarFrameNPC();
}

bool SpriteTrueno::animarMuerteNPC(){
    bool result = false;
    //no es el ultimo frame
    
        if(frActualNPC.x != (cantidadXNPC-1)){
            result = false;
            frActualNPC.x += 1;
        }else{
            frActualNPC.x = 0;
            result = true;
        }
        seleccionarFrameNPC();
    
    return result;
}


//cambiar frame en fila
void SpriteTrueno::cambiarFrameXNPC(int frame){
    //cambio frame en x
    frActualNPC.x = frame;
    seleccionarFrameNPC();
 
}

//cambiar frame en columna
void SpriteTrueno::cambiarFrameYNPC(int frame){
    //cambio frame n y
    frActualNPC.y = frame;
    seleccionarFrameNPC();
}

bool SpriteTrueno::colisionProtagonista(spritePersonaje *sp){
    bool x = false;
    if(spriteNPC->getGlobalBounds().intersects(sp->getSprite().getGlobalBounds())){
        x = true;
    }
    return x;
}