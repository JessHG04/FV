#include <SFML/Graphics.hpp>
#include <iostream>
#include "lara.h"
#include "Enemigo.h"
#include "cuadradoD.h"
#include "bala.h"
#include "mojon.h"
#include "Juego.h"
#include "spritePersonaje.h"
#include "Jugador.h"

using namespace std;
using namespace sf;

#define kVel 5

    lara::lara(int xx, int yy) : Enemigo(3){
        avanza = 0;
        fin = false;
        yasta = false;
        tex = new Texture();
        if (!tex->loadFromFile("resources/Sprites/Lara Croft/401003605_atk.png")) {
            std::cerr << "Error cargando la imagen 401003605_atk.png";
            exit(0);
        } 
        sprite = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        sprite->setOrigin(39, 32);
        //Cojo el sprite que me interesa por defecto del sheet
        sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
        
        // Lo dispongo en el centro de la pantalla
        sprite->setPosition(xx, yy);
        //balera = new bala();
    }

    void lara::cambiarSprite(int x, spritePersonaje *spritep){
        if(x == 0){
            mantener = true;
            shoot = false;
            sprite->setTextureRect(sf::IntRect(142, 350, 34, 52));
            float sgs = mantenedor.getElapsedTime().asSeconds();
            if(sgs >= 2.0){
                mantener = false;
            }
        }
        if(!mantener){
            if(x == 1){
                shoot = false;
                sprite->setTextureRect(sf::IntRect(243, 286, 43, 52));
            }
            if(x == 2){
                shoot = false;
                sprite->setTextureRect(sf::IntRect(33, 351, 37, 52));
            }
            if(x == 3){
                shoot = false;
                sprite->setTextureRect(sf::IntRect(243, 286, 43, 52));
            }
            if(x == 4){
                shoot = false;
                sprite->setTextureRect(sf::IntRect(143, 288, 52, 52));
            }
            if(x == 5){
                shoot = false;
                sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
            }
            if(x == 6){
                shoot = false;
                sprite->setTextureRect(sf::IntRect(228, 12, 73, 52));
            }
            if(x == 7){
                shoot = true;
                sprite->setTextureRect(sf::IntRect(115, 12, 78, 52));
                mantenedor.restart();
            }
        }
        if(spritep->getSprite().getPosition().x < this->getSprite().getPosition().x){
            sprite->setScale(1, 1);
            lado = false;
        }
        else{
            sprite->setScale(-1, 1);
            lado = true;
        }
    }

    void lara::restartSprite(){
        sprite->setColor(Color(255,255,255));
    }

    // x se refiere a la x de la bala, y es 100 mas que la x de lara
    bool lara::Update(RenderWindow &window, spritePersonaje *spritep, int x, int y, Map *mapa){
        if(restartear == true){
            impactado.restart();
            restartear = false;
        }
        this->impactoProyectil();
        if(golpeado == false){
            disparo = false;
            float sgs = reloja.getElapsedTime().asSeconds();
            float sgs4 = relojd.getElapsedTime().asSeconds();
            if(sgs >= 0.1){
                avanza++;
                this->cambiarSprite(avanza, spritep);
                if(avanza == 8){
                    avanza = -1;
                }
                reloja.restart();
            }
            //if(sgs2 >= coolDownDisparo){
            if(shoot == true){
                dispara = true;
                if(lado == false){
                    balera = new bala(x, y);
                }
                else{
                    balera = new bala(x + 32, y);
                }
            }
            else{
                if(balera != nullptr){
                    if(lado == false){
                        if(balera->getSprite()->getPosition().x > x){
                            balera->movimientoBalaDe();
                        }
                        else{
                            balera->movimientoBalaIz();
                        }
                    }
                    else{
                        if(balera->getSprite()->getPosition().x < x){
                            balera->movimientoBalaIz();
                        }
                        else{
                            balera->movimientoBalaDe();
                        }
                    }
                }
            }
            if(balera != nullptr){
                if(this->colisionBalaMapa(balera, mapa)){
                    balera->hacerTransparente();
                    balera->getSprite()->setPosition(0, 0);
                }
            }
            if(balera != nullptr){
                if(sgs4 >= 0.2){
                    if(balera->getSprite()->getGlobalBounds().intersects(spritep->getSprite().getGlobalBounds())){
                        balera->hacerTransparente();
                        disparo = true;
                    }
                    else{
                    }
                    relojd.restart();
                }
            }
        }
        else{
            balera->hacerTransparente();
        }
       return disparo;
    }

    void lara::colisionProtagonista(Jugador *j, bool esGuerrera){
        if((sprite->getGlobalBounds().intersects(j->spr_player->getGlobalBounds()) || j->spr_player->getGlobalBounds().contains(sprite->getOrigin()))  &&  !golpeado){
            if(j->atacando  &&  esGuerrera) {
            golpeado = true;
            restartear = true;
            this->perderVida();
            //j->atacando = false;
            }
        }
    }

    bool lara::colisionProyectil(Proyectil *p1){
        bool x = false;
        if(p1->get_sprite().getGlobalBounds().intersects(sprite->getGlobalBounds()) && golpeado == false){
            this->perderVida();
            x = true;
            golpeado = true;
            restartear = true;           
        }
        return x;
    }

    void lara::impactoProyectil(){
        float sgs = impactado.getElapsedTime().asSeconds();
        if(golpeado == true){
            if(contando % 2 == 0){
                sprite->setColor(Color::Red);
                contando++;
            }
            else{
                this->hacerTransparente();
                contando++;
            }
            if(sgs >= 1){
                this->restartSprite();
                golpeado = false;
            }
        }
    }

    bool lara::morir(){
        bool x = false;
        if(this->getMuerte()){
            x = true;
        }
        return x;
    }

    bool lara::colisionBalaMapa(bala *balera, Map *mapa){ //La colision del personaje con el mapa
    int gid;
    sf::RectangleShape cajaMapa(sf::Vector2f(16, 16)); //Caja de colision de cada GID del mapa
    bool colisionando = false;
        for(unsigned int l = 0; l < 1; l++){
            for(unsigned int y = 0; y < mapa->heightMap; y++){
                for(unsigned int x = 0; x < mapa->widthMap; x++){
                    gid = mapa->tilemap[l][y][x];
                    cajaMapa.setPosition(sf::Vector2f(x*16, y*16));
                    if(gid > 0 && !colisionando){ //Abajo
                        if(cajaMapa.getGlobalBounds().intersects(balera->getSprite()->getGlobalBounds())){
                            balera = new bala(x, y);
                            colisionando = true;
                        }
                    }
                }
            }
        }
        return colisionando;
    }

    void lara::Draw(RenderWindow &window){
        window.draw(*sprite);
    }

    void lara::recibeGolpe(){
        perderVida();
    }

    void lara::hacerTransparente(){
        sprite->setColor(Color::Transparent);
    }

    Sprite lara::getSprite(){
        return *sprite;
    }

    bala lara::getBala(){
        return *balera;
    }