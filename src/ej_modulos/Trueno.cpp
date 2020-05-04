#include "Trueno.h"

Trueno::Trueno(int cantidadX1E, int cantidadY1E , sf::Vector2i frm_actE){
    archivoEne = "resources/Sprites/Trueno/Trueno.png";
    cambiarSpriteNPC(txNPC,cantidadX1E, cantidadY1E, frm_actE);
    velDesplazamientoEne = 2.0f;
}