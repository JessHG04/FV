#include "AnimationKinder.h"

AnimationKinder::AnimationKinder(sf::Texture* texture, float tiempoCambio) {
    this->tiempoCambio = tiempoCambio;
    coordenadasRect = NULL;
    coordActual = NULL;

    // Recortamos la textura...
    float _width, _height;
    _width = texture->getSize().x / 3;
    _height = texture->getSize().y / 4;

    // Asignamos a cada accion sus recortes...
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            if ((i == 0  &&  j == 0)  ||  (i == 3  &&  j == 2))
                coordMovimiento.push_back(sf::IntRect(j*_width, i*_height, _width, _height));
            if (!(i == 3  &&  j == 2))
                coordAtaque.push_back(sf::IntRect(j*_width, i*_height, _width, _height));
            if ((i == 0  &&  j == 0)  ||  (i == 0  &&  j == 1))
                coordEstatico.push_back(sf::IntRect(j*_width, i*_height, _width, _height));
        }
    }

    coordActual = &coordEstatico;
    coordenadasRect = &((*coordActual)[0]);

}


AnimationKinder::~AnimationKinder() {
    coordenadasRect = NULL;
    coordActual = NULL;
    coordAtaque.clear();
    coordEstatico.clear();
    coordMovimiento.clear();
}


void AnimationKinder::UpdateMovement(float deltaTime, int accion) {

    // Comprobamos que accion debe ejecutar...
    if (ejecuta != accion  &&  accion < 3  &&  accion > 0) {
        indice = 0;
        if (accion == 1) {
            coordActual = &coordMovimiento;
            ejecuta = 1;
        } else {
            coordActual = &coordEstatico;
            ejecuta = 2;
        }
    }

    // Realizamos el cambio en la animacion...
    tiempoTotal += deltaTime;
    if (tiempoTotal >= tiempoCambio) {
        tiempoTotal -= tiempoCambio;
        indice++;
        
        if (indice >= int(coordActual->size())) {
            indice = 0;
        }

        coordenadasRect = &((*coordActual)[indice]);
    }
}


bool AnimationKinder::UpdateAttack(float deltaTime) {
    bool _terminado = false;

    // Reseteamos indice...
    if (coordActual) {
        coordActual = NULL;
        indice = 0;
    }
    
    tiempoTotalAtq += deltaTime;
    if (tiempoTotalAtq >= 0.1) {
        tiempoTotalAtq -= 0.1;
        indice++;
        if (indice >= int(coordAtaque.size())) {
            ejecuta = 0;
            _terminado = true;
        } else {
            coordenadasRect = &(coordAtaque[indice]);
        }
    }

    return _terminado;
}


sf::IntRect AnimationKinder::getCoordenadasRect() {
    return (*coordenadasRect);
}


sf::Vector2f AnimationKinder::getOrigin() {
    return sf::Vector2f((*coordenadasRect).width/2, (*coordenadasRect).height);
}


int AnimationKinder::getIndice() {
    return indice;
}