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
        balera = new bala();
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
        sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
        sprite->setScale(1, 1);
    }

    // x se refiere a la x de la bala, y es 100 mas que la x de lara
    void lara::Update(RenderWindow &window, spritePersonaje *spritep, int x, int y){
        float sgs2 = relojb.getElapsedTime().asSeconds();
        float sgs = reloja.getElapsedTime().asSeconds();
        float sgs3 = relojc.getElapsedTime().asSeconds();
        float sgs4 = relojd.getElapsedTime().asSeconds();
        float sgs5 = reloje.getElapsedTime().asSeconds();
        float sgs6 = relojf.getElapsedTime().asSeconds();
        //cout << sgs << endl;
        if(sgs >= 0.5){
            avanza++;
            this->cambiarSprite(avanza, spritep);
            if(avanza == 2){
                // yasta = true;
                avanza = -1;
            }
            reloja.restart();
        }
        // window.clear();
        // larita->Draw(window);
        if(sgs2 >= coolDownDisparo){
            // balera = new bala(x, y);
            balera->restartSprite();
            if(lado == false){
                balera->getSprite()->setPosition(x, y);
            }
            else{
                balera->getSprite()->setPosition(x+50, y);
            }
            /*
            if(es == false){
                cout << balera->getSprite()->getPosition().x << endl;
                cout << this->getSprite().getPosition().x << endl;
                es = true;
            }
            */
            dispara = true;
            //cout << sgs2 << endl;
            //cout << balera << endl;
            // balera->Draw(window);
            relojb.restart();
        }
        else{
            if(balera != nullptr){
                if(lado == false){
                    balera->movimientoBalaIz();
                    /*
                    if(balera->getSprite()->getPosition().x <= (this->getSprite().getPosition().x+100)){
                        balera->movimientoBalaIz();
                    }
                    else{
                        balera->getSprite()->setPosition(x, y);
                        balera->movimientoBalaDe();
                    }
                    //balera->Draw(window);
                    */
                }
                else{
                     balera->movimientoBalaDe();
                }
            }
        }
        if(balera != nullptr){
            if(sgs4 >= 0.2){
                if(balera->getSprite()->getGlobalBounds().intersects(spritep->getSprite().getGlobalBounds())){
                    cout << "Le quita 1 vida al personaje" << endl;
                    //mojonillo->perderVida();
                    //cout << "Mojon: " << mojonillo->getNumVidas() << endl;
                    //mojonillo->hacerTransparente();
                    balera->hacerTransparente();
                }
                else{
                    //mojonillo->restartSprite();
                }
                relojd.restart();
            }
        }
        // Funcionalidad que sera anyadida en el proximo hito
        /*
        if(sgs3 >= 1) {
            if(spritep->getSprite().getGlobalBounds().intersects(this->getSprite().getGlobalBounds())){
                cout << "Le quita 1 vida a lara" << endl;
                this->recibeGolpe();
                cout << "Lara: " << this->getNumVidas() << endl;
                sprite->setColor(Color::Transparent);
            }
            else{
                sprite->setColor(Color(255,255,255));
            }
            relojc.restart();
        }
        */
    }

    void lara::Draw(RenderWindow &window){
        window.draw(*sprite);
    }

    void lara::recibeGolpe(){
        perderVida();
    }

    Sprite lara::getSprite(){
        return *sprite;
    }

    bala lara::getBala(){
        return *balera;
    }