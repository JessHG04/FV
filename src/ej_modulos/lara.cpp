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
            sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
        }
        else if(x == 1){
            sprite->setTextureRect(sf::IntRect(228, 12, 73, 52));
        }
        else{
            sprite->setTextureRect(sf::IntRect(115, 12, 78, 52));
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
    bool lara::Update(RenderWindow &window, spritePersonaje *spritep, int x, int y){
        if(restartear == true){
            impactado.restart();
            restartear = false;
        }
        this->impactoProyectil();
        if(golpeado == false){
            disparo = false;
            float sgs2 = relojb.getElapsedTime().asSeconds();
            float sgs = reloja.getElapsedTime().asSeconds();
            float sgs3 = relojc.getElapsedTime().asSeconds();
            float sgs4 = relojd.getElapsedTime().asSeconds();
            float sgs5 = reloje.getElapsedTime().asSeconds();
            float sgs6 = relojf.getElapsedTime().asSeconds();
            if(sgs >= 0.5){
                avanza++;
                this->cambiarSprite(avanza, spritep);
                if(avanza == 2){
                    avanza = -1;
                }
                reloja.restart();
            }
            if(sgs2 >= coolDownDisparo){
                if(lado == false){
                    balera = new bala(x, y);
                }
                else{
                    balera = new bala(x + 50, y);
                }
                dispara = true;
                relojb.restart();
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
       return disparo;
    }

    bool lara::colisionProyectil(Proyectil *p1){
        bool x = false;
        if(p1->get_sprite().getGlobalBounds().intersects(sprite->getGlobalBounds()) && golpeado == false){
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