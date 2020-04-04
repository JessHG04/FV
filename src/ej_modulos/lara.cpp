#include <SFML/Graphics.hpp>
#include <iostream>
#include "lara.h"
#include "Enemigo.h"
#include "cuadradoD.h"
#include "bala.h"
#include "mojon.h"

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
    }

    void lara::cambiarSprite(int x){
        if(x == 0){
            sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
        }
        if(x == 1){
            sprite->setTextureRect(sf::IntRect(228, 12, 73, 52));
        }
        if(x == 2){
            sprite->setTextureRect(sf::IntRect(115, 12, 78, 52));
        }
        sprite->setScale(1, 1);
    }

    void lara::restartSprite(){
        sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
        sprite->setScale(1, 1);
    }

    // x se refiere a la x de la bala, y es 100 mas que la x de lara
    void lara::Update(RenderWindow &window, mojon *mojonillo, int x, int y){
        float sgs2 = relojb.getElapsedTime().asSeconds();
        float sgs = reloja.getElapsedTime().asSeconds();
        float sgs3 = relojc.getElapsedTime().asSeconds();
        float sgs4 = relojd.getElapsedTime().asSeconds();
        //cout << sgs << endl;
        if(sgs >= 1){
            avanza++;
            this->cambiarSprite(avanza);
            if(avanza == 2){
                // yasta = true;
                avanza = -1;
            }
            reloja.restart();
        }
        // window.clear();
        // larita->Draw(window);
        if(sgs2 >= coolDownDisparo){
            balera = new bala(x, y);
            //cout << sgs2 << endl;
            window.draw(balera->getSprite());
            relojb.restart();
        }
        else{
            if(balera != nullptr){
                balera->movimientoBala();
                window.draw(balera->getSprite());
            }
        }
        if(balera != nullptr){
            if(sgs4 >= 0.2){
                if(balera->getSprite().getGlobalBounds().intersects(mojonillo->getSprite().getGlobalBounds())){
                    cout << "Le quita 1 vida al mojon" << endl;
                    mojonillo->perderVida();
                    cout << "Mojon: " << mojonillo->getNumVidas() << endl;
                    mojonillo->hacerTransparente();
                    balera->hacerTransparente();
                }
                else{
                    mojonillo->restartSprite();
                }
                relojd.restart();
            }
        }
        if(sgs3 >= 1) {
            if(mojonillo->getSprite().getGlobalBounds().intersects(this->getSprite().getGlobalBounds())){
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