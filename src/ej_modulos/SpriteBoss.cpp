#include "SpriteBoss.h"
using namespace std;
#include <iostream>

//constrcutor   
SpriteBoss::SpriteBoss(){
    //textura de imagen
    txBoss = new sf::Texture();
    //cargo la textura
    //ruta de acceso al sprite
    sf::String ruta = "resources/Sprites/Boss/BossFinal.png";
    //cargar textura
    txBoss->loadFromFile(ruta);
    txBoss->setSmooth(true);
    //nuevo sprite a partir de la textura
    spriteBoss = new sf::Sprite(*txBoss);
}

//cambiar sprite
void SpriteBoss::cambiarSpriteBoss(sf::Texture *textura, int n1, int n2, sf::Vector2i frm){
    //grids en x
    cantidadXBoss = n1;
    //grids en y
    cantidadYBoss = n2;
    txActualBoss = textura;

    spriteBoss->setOrigin((txActualBoss->getSize().x / cantidadXBoss) / 2, (txActualBoss->getSize().y / cantidadYBoss) / 2);
    //spriteJugador->setOrigin((txActual->getSize().x) / 2, (txActual->getSize().y / 2));
    spriteBoss->setTexture(*textura);
    tamFrameBoss = sf::Vector2f(txActualBoss->getSize().x / cantidadXBoss, txActualBoss->getSize().y / cantidadYBoss); //Dimension de cada frame haciendo la operacion    
    frActualBoss = frm; // cogemos el frame que queremos utilizar
    spriteBoss->setScale(0.45,0.45);
    seleccionarFrameBoss(); 
    sf::RectangleShape box(sf::Vector2f(tamFrameBoss.x, tamFrameBoss.y));
    cajaColisionesBoss = box;
    cajaColisionesBoss.setFillColor(sf::Color::Transparent);
}

//carga el frame correspondiente actual
void SpriteBoss::seleccionarFrameBoss(){
    sf::IntRect rectangulo(frActualBoss.x * tamFrameBoss.x,frActualBoss.y * tamFrameBoss.y,tamFrameBoss.x,tamFrameBoss.y); //Construimos el rectangulo del tamaño del frame que queremos
    spriteBoss->setTextureRect(rectangulo); // le insertamos el recorte al sprite
}

//animacion
void SpriteBoss::animarBoss(){
    //no es el ultimo frame
    if(frActualBoss.x != (cantidadXBoss-1)){
        frActualBoss.x += 1;
    }else{
        frActualBoss.x = 0;
    }
    seleccionarFrameBoss();
}

bool SpriteBoss::animarMuerteBoss(){
    bool result = false;
    //no es el ultimo frame
    
        if(frActualBoss.x != (cantidadXBoss-1)){
            result = false;
            frActualBoss.x += 1;
        }else{
            frActualBoss.x = 0;
            result = true;
        }
        seleccionarFrameBoss();
    
    return result;
}


//cambiar frame en fila
void SpriteBoss::cambiarFrameXBoss(int frame){
    //cambio frame en x
    frActualBoss.x = frame;
    seleccionarFrameBoss();
 
}

//cambiar frame en columna
void SpriteBoss::cambiarFrameYBoss(int frame){
    //cambio frame n y
    frActualBoss.y = frame;
    seleccionarFrameBoss();
}