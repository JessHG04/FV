#include "Enemigo.h"

Enemigo::Enemigo(int vidas) {
    this->vidas = vidas;
}

Enemigo::~Enemigo() {

}

void Enemigo::perderVida(){
    if(!muerto){
        vidas--;
        if(vidas == 0){
            muerto = true;
        }
    }
}

bool Enemigo::getMuerte(){
    return muerto;
}

int Enemigo::getNumVidas(){
    return this->vidas;
}
