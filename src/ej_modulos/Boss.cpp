#include "Boss.h"

using namespace std;

Boss::Boss(){
    vida = 10;
}

//actualiza al enemigo
void Boss::updateBoss(){
    if(restartear == true){
        impactado.restart();
        restartear = false;
    }
    float sgs = relojAnimacion.getElapsedTime().asSeconds();
    if(sgs >= 0.5){
        this->animarBoss();
        relojAnimacion.restart();
    }
    this->impactoProyectil(); 

    setTraBoss(velBoss);
    cajaColisionesBoss.setPosition(getPosicionBoss().x - tamFrameBoss.x/6 + 15, getPosicionBoss().y- tamFrameBoss.y/4);

}

void Boss::perderVida(){
    if(!muerto){
        vida--;
        if(vida == 0){
            muerto = true;
        }
    }
}

void Boss::colocarBoss(){
    spriteBoss->setPosition(0, 0);
}

bool Boss::getMuerte(){
    return muerto;
}

void Boss::setMuerte(bool morir){
    muerto = morir;
}

void Boss::impactoProyectil(){
    float sgs = impactado.getElapsedTime().asSeconds();
    if(golpeado == true){
        if(contando % 2 == 0){
            spriteBoss->setColor(sf::Color::Red);
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

bool Boss::colisionProyectil(Proyectil *p1){
    bool x = false;
    if(p1->get_sprite().getGlobalBounds().intersects(cajaColisionesBoss.getGlobalBounds()) && golpeado == false){
        this->perderVida();
        x = true;
        golpeado = true;
        restartear = true;           
    }
    return x;
}

bool Boss::morir(){
    bool x = false;
    if(this->getMuerte()){
        x = true;
    }
    return x;
}

void Boss::hacerTransparente(){
    spriteBoss->setColor(sf::Color::Transparent);
}

void Boss::restartSprite(){
    spriteBoss->setColor(sf::Color(255,255,255));
}

bool Boss::colisionProtagonista(Jugador *j, bool esGuerrera){
    bool x = false;
    //std::cout << "Caja protagonista " << j->cajaColisiones3.getPosition().x << " " << j->cajaColisiones3.getPosition().y << std::endl;
    //std::cout << "Caja boss " << cajaColisionesBoss.getPosition().x << " " << cajaColisionesBoss.getPosition().y << std::endl;

    if(j->getSprite().getGlobalBounds().intersects(cajaColisionesBoss.getGlobalBounds()) && golpeado == false){
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
