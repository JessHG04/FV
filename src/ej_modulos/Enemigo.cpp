#include "Enemigo.h"

Enemigo::Enemigo() {
    // constructor por defecto
}

Enemigo::Enemigo(int vidas) {
    this->vidas = vidas;
}

Enemigo::~Enemigo() {
    // Destruye su corespondiente NPC
}

int Enemigo::getNumVidas(){
    return this->vidas;
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

void Enemigo::setMuerte(bool morir){
    muerto = morir;
}

bool Enemigo::colisionProyectil(Proyectil *p1){
    
}
void Enemigo::recibeGolpe() {
    // Golpea su corespondiente NPC
}


void Enemigo::Update(float deltaTime) {
    // Actualiza su corespondiente NPC
}


void Enemigo::Draw(RenderWindow &window) {
    // Dibuja su corespondiente NPC
}