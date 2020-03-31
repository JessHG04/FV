#include <SFML/Graphics.hpp>
#include <iostream>
#include "lara.h"
#include "Enemigo.h"
#include "cuadradoD.h"
#include "bala.h"

using namespace std;
using namespace sf;

#define kVel 5

    lara::lara() : Enemigo(3){
        avanza = 0;
        fin = false;
        yasta = false;
        tex = new Texture();
        if (!tex->loadFromFile("resources/401003605_atk.png")) {
            std::cerr << "Error cargando la imagen 401003605_atk.png";
            exit(0);
        } 
        sprite = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        sprite->setOrigin(39, 32);
        //Cojo el sprite que me interesa por defecto del sheet
        sprite->setTextureRect(sf::IntRect(31, 12, 47, 52));
        
        // Lo dispongo en el centro de la pantalla
        sprite->setPosition(550, 240);
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

    void lara::Update(RenderWindow &window, lara *larita, cuadradoD *cuadri){
        float sgs2 = relojb.getElapsedTime().asSeconds();
        float sgs = reloja.getElapsedTime().asSeconds();
        cout << sgs << endl;
        if(sgs >= 2){
            avanza++;
            larita->cambiarSprite(avanza);
            if(avanza == 2){
                // yasta = true;
                avanza = -1;
            }
            reloja.restart();
        }
        // window.clear();
        // larita->Draw(window);
        if(sgs2 >= coolDownDisparo){
            balera = new bala();
            cout << sgs2 << endl;
            window.draw(balera->devolverSprite());
            relojb.restart();
        }
        else{
            if(balera != nullptr){
                balera->movimientoBala();
//                larita->cambiarSprite(avanza);
                window.draw(balera->devolverSprite());
            }
        }
        if(balera != nullptr){
            if(balera->devolverSprite().getGlobalBounds().intersects(cuadri->devolverSprite2().getGlobalBounds())){
                cout << "Colision con el cuadrado" << endl;
            }
        }
    }

    void lara::Draw(RenderWindow &window){
        window.draw(*sprite);
    }

    Sprite lara::devolverSprite(){
        return *sprite;
    }