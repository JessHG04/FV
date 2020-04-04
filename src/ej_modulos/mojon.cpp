#include <SFML/Graphics.hpp>
#include <iostream>
#include "mojon.h"
#include "cuadradoD.h"
#include "cuadradoI.h"
#include "Enemigo.h"
#include "lara.h"

using namespace std;
using namespace sf;

#define kVel 10

    mojon::mojon(int xx, int yy, int pos1, int pos2) : Enemigo(6){
        direccion = 0;
        avansa = 0;
        x = xx;
        y = yy;
        posx = pos1;
        posxx = pos2;
        tex = new Texture();
        if (!tex->loadFromFile("resources/Sprites/Mojon/sprite_player.png")) {
            std::cerr << "Error cargando la imagen sprite_player.png";
            exit(0);
        } 
        sprite = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        sprite->setOrigin(24, 189);
        //Cojo el sprite que me interesa por defecto del sheet
        sprite->setTextureRect(sf::IntRect(15, 164, 18, 50));
        
        // Lo dispongo en el centro de la pantalla
        sprite->setPosition(xx, yy);
    }

    mojon::~mojon() {

    }
    
    void mojon::Update(){
        float sgs = reloj.getElapsedTime().asSeconds();
        if(sgs >= 0.10){
          if(this->direccion == 0){
            this->cambiarSprite(avansa);
            if(this->getSprite().getPosition().x >= posxx){
              this->direccion = 1;
            }
          }
          else{
            this->cambiarSpriteDos(avansa);
            if(this->getSprite().getPosition().x <= posx){
              this->direccion = 0;
            }
          }
          avansa++;
          if(avansa == 8){
            avansa = 0;
          }
          reloj.restart();
        }   
    }

    void mojon::cambiarSprite(int x){
        if(x == 0){
            sprite->setTextureRect(sf::IntRect(15, 164, 18, 50));
            sprite->move(kVel, 0);
        }
        if(x == 1){
            sprite->setTextureRect(sf::IntRect(67, 163, 27, 50));
            sprite->move(kVel, 0);
        }
        if(x == 2){
            sprite->setTextureRect(sf::IntRect(114, 160, 24, 54));
            sprite->move(kVel, 0);
        }
        if(x == 3){
            sprite->setTextureRect(sf::IntRect(164, 160, 26, 53));
            sprite->move(kVel, 0);
        }
        if(x == 4){
            sprite->setTextureRect(sf::IntRect(220, 158, 21, 56));
            sprite->move(kVel, 0);
        }
        if(x == 5){
            sprite->setTextureRect(sf::IntRect(272, 161, 30, 52));
            sprite->move(kVel, 0);
        }
        if(x == 6){
            sprite->setTextureRect(sf::IntRect(322, 163, 32, 50));
            sprite->move(kVel, 0);
        }
        if(x == 7){
            sprite->setTextureRect(sf::IntRect(376, 164, 24, 50));
            sprite->move(kVel, 0);
        }
        sprite->setScale(1, 1);
    }

    void mojon::cambiarSpriteDos(int x){
        /*
        if(x == 0){
            sprite->setTextureRect(sf::IntRect(19, 89, 18, ));
            sprite->move(-kVel, 0);50
        }
        if(x == 1){
            sprite->setTextureRect(sf::IntRect(61, 87, 27, 51));
            sprite->move(-kVel, 0);
        }
        if(x == 2){
            sprite->setTextureRect(sf::IntRect(120, 84, 24, 54));
            sprite->move(-kVel, 0);
        }
        if(x == 3){
            sprite->setTextureRect(sf::IntRect(170, 87, 26, 53));
            sprite->move(-kVel, 0);
        }
        if(x == 4){
            sprite->setTextureRect(sf::IntRect(222, 85, 21, 56));
            sprite->move(-kVel, 0);
        }
        if(x == 5){
            sprite->setTextureRect(sf::IntRect(269, 89, 30, 52));
            sprite->move(-kVel, 0);
        }
        if(x == 6){
            sprite->setTextureRect(sf::IntRect(321, 90, 32, 50));
            sprite->move(-kVel, 0);
        }
        if(x == 7){
        sprite->setTextureRect(sf::IntRect(377, 90, 24, 50));
            sprite->move(kVel, 0);
        }
        sprite->setScale(1, 1);
        */
        if(x == 0){
            sprite->setTextureRect(sf::IntRect(19, 89, 18, 50));
            sprite->move(-kVel, 0);
        }
        if(x == 1){
            sprite->setTextureRect(sf::IntRect(61, 87, 27, 51));
            sprite->move(-kVel, 0);
        }
        if(x == 2){
            sprite->setTextureRect(sf::IntRect(120, 84, 24, 54));
            sprite->move(-kVel, 0);
        }
        if(x == 3){
            sprite->setTextureRect(sf::IntRect(170, 87, 26, 53));
            sprite->move(-kVel, 0);
        }
        if(x == 4){
            sprite->setTextureRect(sf::IntRect(222, 85, 21, 56));
            sprite->move(-kVel, 0);
        }
        if(x == 5){
            sprite->setTextureRect(sf::IntRect(269, 89, 30, 52));
            sprite->move(-kVel, 0);
        }
        if(x == 6){
            sprite->setTextureRect(sf::IntRect(321, 90, 32, 50));
            sprite->move(-kVel, 0);
        }
        if(x == 7){
        sprite->setTextureRect(sf::IntRect(377, 90, 24, 50));
            sprite->move(-kVel, 0);
        }
        sprite->setScale(1, 1);
    }

    void mojon::Draw(RenderWindow &window){
        window.draw(*sprite);
    }

    void mojon::recibeGolpe(){
        perderVida();
    }

    void mojon::hacerTransparente(){
        sprite->setColor(Color::Transparent);
    }

    void mojon::restartSprite(){
        sprite->setColor(Color(255,255,255));
    }

    Sprite mojon::getSprite(){
        return *sprite;
    }