#include "mojon.h"

using namespace std;
using namespace sf;

#define kVel 10

    mojon::mojon(int xx, int yy, int pos1, int pos2, bool grandesito) : Enemigo(6){
        direccion = 0;
        avansa = 0;
        x = xx;
        y = yy;
        posx = pos1;
        posxx = pos2;
        grande = grandesito;
        tex = new Texture();
        if (!tex->loadFromFile("resources/Sprites/Mojon/mojonazo.png")) {
            std::cerr << "Error cargando la imagen mojonazo.png";
            exit(0);
        } 
        sprite = new Sprite(*tex);
        //Le pongo el centroide donde corresponde
        sprite->setOrigin(24, 189);
        //Cojo el sprite que me interesa por defecto del sheet
        sprite->setTextureRect(sf::IntRect(15, 164, 18, 50));
        // Lo dispongo en el centro de la pantalla
        sprite->setPosition(xx, yy);
        if(grande){
            sprite->setScale(2.0, 2.0);
        }
    }

    mojon::~mojon() {

    }
    
    void mojon::Update(float nada){
        if(restartear == true){
            impactado.restart();
            restartear = false;
        }
        this->impactoProyectil();
        if(golpeado == false){
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
            if(avansa == 4){
                avansa = 0;
            }
            reloj.restart();
            }   
        }
    }

    bool mojon::colisionProyectil(Proyectil *p1){
        bool x = false;
        if(p1->get_sprite().getGlobalBounds().intersects(sprite->getGlobalBounds()) && golpeado == false){
            this->perderVida();
            //cout << "Num vidas: " << this->getNumVidas() << endl;
            x = true;
            golpeado = true;
            restartear = true;           
        }
        return x;
    }

    void mojon::impactoProyectil(){
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
            if(sgs >= 1.0f){
                this->restartSprite();
                golpeado = false;
            }
        }
    }

    bool mojon::colisionProtagonista(Jugador *j, bool esGuerrera){
        bool x = false;

          if((sprite->getGlobalBounds().intersects(j->spr_player->getGlobalBounds()) || j->spr_player->getGlobalBounds().contains(sprite->getOrigin()))  &&  !golpeado){
            if(j->atacando  &&  esGuerrera) {
              //std::cout << "holaaaaaa" << std::endl;
              golpeado = true;
              restartear = true;
              this->perderVida();
              //j->atacando = false;
            } else { x = true; }
          }

          return x;
    }

    void mojon::cambiarSprite(int x){
        if(x == 0){
            sprite->setTextureRect(sf::IntRect(2, 114, 62, 54));
            sprite->move(kVel, 0);
        }
        if(x == 1){
            sprite->setTextureRect(sf::IntRect(66, 115, 61, 54));
            sprite->move(kVel, 0);
        }
        if(x == 2){
            sprite->setTextureRect(sf::IntRect(130, 114, 62, 54));
            sprite->move(kVel, 0);
        }
        if(x == 3){
            sprite->setTextureRect(sf::IntRect(194, 115, 61, 53));
            sprite->move(kVel, 0);
        }
        sprite->setScale(1, 1);
    }

    void mojon::cambiarSpriteDos(int x){
        if(x == 0){
            sprite->setTextureRect(sf::IntRect(1, 59, 61, 53));
            sprite->move(-kVel, 0);
        }
        if(x == 1){
            sprite->setTextureRect(sf::IntRect(65, 59, 61, 53));
            sprite->move(-kVel, 0);
        }
        if(x == 2){
            sprite->setTextureRect(sf::IntRect(129, 59, 61, 53));
            sprite->move(-kVel, 0);
        }
        if(x == 3){
            sprite->setTextureRect(sf::IntRect(193, 59, 61, 53));
            sprite->move(-kVel, 0);
        }
        sprite->setScale(1, 1);
    }

    bool mojon::morir(){
        bool x = false;
        if(this->getMuerte()){
            x = true;
        }
        return x;
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

    void mojon::hacerGrande(){
        sprite->setScale(10.0, 10.0);
        //Cambiar vida
    }

    void mojon::restartSprite(){
        sprite->setColor(Color(255,255,255));
    }

    Sprite mojon::getSprite(){
        return *sprite;
    }
